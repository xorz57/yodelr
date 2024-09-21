#include <gtest/gtest.h>

#include <yodelr/yodelr_impl.h>

class YodelrTest : public testing::Test {
protected:
    std::unique_ptr<yodelr::Yodelr> service;

    void SetUp() override {
        service = std::make_unique<yodelr::YodelrImpl>();

        service->addUser("john");
    }

    void TearDown() override {
        service.reset();
    }
};

TEST_F(YodelrTest, AddUserAndCheckPosts) {
    service->addPost("john", "just #chilling today", 1);
    service->addPost("john", "eating #steak for dinner", 2);

    auto postTexts = service->getPostsForUser("john");
    EXPECT_EQ(postTexts.size(), 2);
    EXPECT_EQ(postTexts[0], "eating #steak for dinner");
    EXPECT_EQ(postTexts[1], "just #chilling today");
}

TEST_F(YodelrTest, AddPostAndCheckTopic) {
    service->addPost("john", "just #chilling today", 1);
    service->addPost("john", "eating #steak for dinner", 2);
    service->addPost("john", "ugh! this #steak tasted like dog food", 3);

    auto postTexts = service->getPostsForTopic("steak");
    EXPECT_EQ(postTexts.size(), 2);
    EXPECT_EQ(postTexts[0], "ugh! this #steak tasted like dog food");
    EXPECT_EQ(postTexts[1], "eating #steak for dinner");
}

TEST_F(YodelrTest, DeleteUser) {
    service->addPost("john", "just #chilling today", 1);
    service->addPost("john", "eating #steak for dinner", 2);

    service->deleteUser("john");

    auto postTexts = service->getPostsForUser("john");
    EXPECT_TRUE(postTexts.empty());
}

TEST_F(YodelrTest, GetTrendingTopics) {
    service->addPost("john", "just #chilling today", 1);
    service->addPost("john", "eating #steak for dinner", 2);
    service->addPost("john", "ugh! this #steak tasted like dog food", 3);

    auto topics = service->getTrendingTopics(1, 3);
    EXPECT_EQ(topics.size(), 2);
    EXPECT_EQ(topics[0], "steak");
    EXPECT_EQ(topics[1], "chilling");
}

TEST_F(YodelrTest, NoPostsForNonExistentTopic) {
    service->addPost("john", "just #chilling today", 1);

    auto postTexts = service->getPostsForTopic("nonexistent");
    EXPECT_TRUE(postTexts.empty());
}
