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

TEST_F(YodelrTest, GetPostsForUser) {
    service->addUser("user1");
    service->addPost("user1", "post1 with #topic1", 1);
    service->addPost("user1", "post3 with #topic3", 3);

    service->addUser("user2");
    service->addPost("user2", "post4 with #topic4", 4);
    service->addPost("user2", "post2 with #topic2", 2);

    auto user3PostTexts = service->getPostsForUser("user3");
    EXPECT_TRUE(user3PostTexts.empty());

    auto user1PostTexts = service->getPostsForUser("user1");
    EXPECT_EQ(user1PostTexts.size(), 2);
    EXPECT_EQ(user1PostTexts[0], "post3 with #topic3");
    EXPECT_EQ(user1PostTexts[1], "post1 with #topic1");

    auto user2PostTexts = service->getPostsForUser("user2");
    EXPECT_EQ(user2PostTexts.size(), 2);
    EXPECT_EQ(user2PostTexts[0], "post4 with #topic4");
    EXPECT_EQ(user2PostTexts[1], "post2 with #topic2");
}

TEST_F(YodelrTest, GetPostsForTopic) {
    service->addUser("user1");
    service->addPost("user1", "post1 with #topic1 and #topic2", 1);

    service->addUser("user2");
    service->addPost("user2", "post2 with #topic2", 2);

    auto topic3PostTexts = service->getPostsForTopic("topic3");
    EXPECT_EQ(topic3PostTexts.size(), 0);

    auto topic2PostTexts = service->getPostsForTopic("topic2");
    EXPECT_EQ(topic2PostTexts.size(), 2);
    EXPECT_EQ(topic2PostTexts[0], "post2 with #topic2");
    EXPECT_EQ(topic2PostTexts[1], "post1 with #topic1 and #topic2");
}

TEST_F(YodelrTest, DeleteUser) {
    service->addUser("user1");
    service->addPost("user1", "post1 with #topic1", 1);
    service->addPost("user1", "post2 with #topic2", 2);

    service->addUser("user2");
    service->addPost("user2", "post3 with #topic1", 3);
    service->addPost("user2", "post4 with #topic2", 4);

    service->deleteUser("user1");

    auto user1PostTexts = service->getPostsForUser("user1");
    EXPECT_TRUE(user1PostTexts.empty());

    auto topic1PostTexts = service->getPostsForTopic("topic1");
    EXPECT_EQ(topic1PostTexts.size(), 1);
    EXPECT_EQ(topic1PostTexts[0], "post3 with #topic1");

    auto topic2PostTexts = service->getPostsForTopic("topic2");
    EXPECT_EQ(topic2PostTexts.size(), 1);
    EXPECT_EQ(topic2PostTexts[0], "post4 with #topic2");
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
