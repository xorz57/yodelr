#include <gtest/gtest.h>
#include <yodelr/yodelr_impl.h>

#include <memory>

class YodelrTest : public testing::Test {
protected:
    std::unique_ptr<yodelr::Yodelr> service;

    void SetUp() override {
        service = std::make_unique<yodelr::YodelrImpl>();
    }

    void TearDown() override {
        service.reset();
    }
};

TEST_F(YodelrTest, AddUser) {
    service->addUser("alice");

    auto postTexts = service->getPostsForUser("alice");
    EXPECT_TRUE(postTexts.empty());
}

TEST_F(YodelrTest, AddPostAndCheckUserPostsOrder) {
    service->addUser("bob");
    service->addPost("bob", "post one with #topic1", 10);
    service->addPost("bob", "post two with #topic2", 20);

    auto postTexts = service->getPostsForUser("bob");
    EXPECT_EQ(postTexts.size(), 2);
    EXPECT_EQ(postTexts[0], "post two with #topic2");
    EXPECT_EQ(postTexts[1], "post one with #topic1");
}

TEST_F(YodelrTest, AddPostAndCheckTopic) {
    service->addUser("charlie");
    service->addPost("charlie", "learning #cpp and #programming", 1);
    service->addPost("charlie", "enjoying #programming!", 2);

    auto postTexts = service->getPostsForTopic("programming");
    EXPECT_EQ(postTexts.size(), 2);
    EXPECT_EQ(postTexts[0], "enjoying #programming!");
    EXPECT_EQ(postTexts[1], "learning #cpp and #programming");
}

TEST_F(YodelrTest, DeleteUserRemovesPosts) {
    service->addUser("dave");
    service->addPost("dave", "post #one", 1);
    service->addPost("dave", "post #two", 2);

    service->deleteUser("dave");

    auto postTexts = service->getPostsForUser("dave");
    EXPECT_TRUE(postTexts.empty());
}

TEST_F(YodelrTest, GetTrendingTopicsNoPosts) {
    auto topics = service->getTrendingTopics(0, 10);
    EXPECT_TRUE(topics.empty());
}

TEST_F(YodelrTest, GetTrendingTopicsWithSinglePost) {
    service->addUser("eve");
    service->addPost("eve", "this is a test #testing post", 5);

    auto topics = service->getTrendingTopics(0, 10);
    EXPECT_EQ(topics.size(), 1);
    EXPECT_EQ(topics[0], "testing");
}

TEST_F(YodelrTest, GetTrendingTopicsMultiplePosts) {
    service->addUser("frank");
    service->addPost("frank", "#cpp is great", 1);
    service->addPost("frank", "#cpp and #programming are awesome", 2);
    service->addPost("frank", "#cpp is my favorite!", 3);

    auto topics = service->getTrendingTopics(1, 3);
    EXPECT_EQ(topics.size(), 2);
    EXPECT_EQ(topics[0], "cpp");
    EXPECT_EQ(topics[1], "programming");
}

TEST_F(YodelrTest, NoPostsForNonExistentTopic) {
    service->addUser("george");
    service->addPost("george", "just do it", 1);

    auto postTexts = service->getPostsForTopic("nonexistent");
    EXPECT_TRUE(postTexts.empty());
}

TEST_F(YodelrTest, HandleMultipleUsersAndPosts) {
    service->addUser("henry");
    service->addPost("henry", "#tech is evolving", 10);

    service->addUser("irene");
    service->addPost("irene", "#tech and #innovation go hand in hand", 20);

    auto topics = service->getTrendingTopics(0, 30);
    EXPECT_EQ(topics.size(), 2);
    EXPECT_EQ(topics[0], "tech");
    EXPECT_EQ(topics[1], "innovation");
}
