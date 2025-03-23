#include "yodelr/yodelr_impl.h"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

using ::testing::Test;

class YodelrTest : public Test {
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

    const auto user3PostTexts = service->getPostsForUser("user3");
    EXPECT_TRUE(user3PostTexts.empty());

    const auto user1PostTexts = service->getPostsForUser("user1");
    EXPECT_EQ(user1PostTexts.size(), 2);
    EXPECT_EQ(user1PostTexts[0], "post3 with #topic3");
    EXPECT_EQ(user1PostTexts[1], "post1 with #topic1");

    const auto user2PostTexts = service->getPostsForUser("user2");
    EXPECT_EQ(user2PostTexts.size(), 2);
    EXPECT_EQ(user2PostTexts[0], "post4 with #topic4");
    EXPECT_EQ(user2PostTexts[1], "post2 with #topic2");
}

TEST_F(YodelrTest, AddPostExceedsCharacterLimit) {
    const std::string postText(141, '?');

    EXPECT_THROW(service->addPost("user1", postText, 1), std::length_error);
}

TEST_F(YodelrTest, GetPostsForTopic) {
    service->addUser("user1");
    service->addPost("user1", "post1 with #topic1 and #topic2", 1);

    service->addUser("user2");
    service->addPost("user2", "post2 with #topic2", 2);

    const auto topic3PostTexts = service->getPostsForTopic("topic3");
    EXPECT_EQ(topic3PostTexts.size(), 0);

    const auto topic2PostTexts = service->getPostsForTopic("topic2");
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

    const auto user1PostTexts = service->getPostsForUser("user1");
    EXPECT_TRUE(user1PostTexts.empty());

    const auto topic1PostTexts = service->getPostsForTopic("topic1");
    EXPECT_EQ(topic1PostTexts.size(), 1);
    EXPECT_EQ(topic1PostTexts[0], "post3 with #topic1");

    const auto topic2PostTexts = service->getPostsForTopic("topic2");
    EXPECT_EQ(topic2PostTexts.size(), 1);
    EXPECT_EQ(topic2PostTexts[0], "post4 with #topic2");
}

TEST_F(YodelrTest, GetTrendingTopics) {
    service->addUser("user1");
    service->addPost("user1", "post1 with #topic1", 11);
    service->addPost("user1", "post3 with #topic1", 13);
    service->addPost("user1", "post4 with #topic4", 14);

    service->addUser("user2");
    service->addPost("user2", "post2 with #topic1 and #topic2", 12);
    service->addPost("user2", "post5 with #topic2 and #topic3", 15);

    const auto trendingTopicsFrom1To10 = service->getTrendingTopics(1, 10);
    EXPECT_EQ(trendingTopicsFrom1To10.size(), 0);

    const auto trendingTopicsFrom21To30 = service->getTrendingTopics(21, 30);
    EXPECT_EQ(trendingTopicsFrom21To30.size(), 0);

    const auto trendingTopicsFrom1To13 = service->getTrendingTopics(1, 13);
    EXPECT_EQ(trendingTopicsFrom1To13.size(), 2);
    EXPECT_EQ(trendingTopicsFrom1To13[0], "topic1");// 3 times
    EXPECT_EQ(trendingTopicsFrom1To13[1], "topic2");// 1 time

    const auto trendingTopicsFrom11To20 = service->getTrendingTopics(11, 20);
    EXPECT_EQ(trendingTopicsFrom11To20.size(), 4);
    EXPECT_EQ(trendingTopicsFrom11To20[0], "topic1");// 3 times
    EXPECT_EQ(trendingTopicsFrom11To20[1], "topic2");// 2 times
    EXPECT_EQ(trendingTopicsFrom11To20[2], "topic3");// 1 time
    EXPECT_EQ(trendingTopicsFrom11To20[3], "topic4");// 1 time

    const auto trendingTopicsFrom14To20 = service->getTrendingTopics(14, 20);
    EXPECT_EQ(trendingTopicsFrom14To20.size(), 3);
    EXPECT_EQ(trendingTopicsFrom14To20[0], "topic2");// 1 time
    EXPECT_EQ(trendingTopicsFrom14To20[1], "topic3");// 1 time
    EXPECT_EQ(trendingTopicsFrom14To20[2], "topic4");// 1 time
}

TEST_F(YodelrTest, GetTrendingTopicsOrder) {
    service->addUser("user1");
    service->addPost("user1", "post1 with #topic1", 11);
    service->addPost("user1", "post2 with #topic2", 12);
    service->addPost("user1", "post3 with #topic1", 13);
    service->addPost("user1", "post4 with #topic3", 14);
    service->addPost("user1", "post5 with #topic3", 15);
    service->addPost("user1", "post6 with #topic2", 16);
    service->addPost("user1", "post7 with #topic2", 17);
    service->addPost("user1", "post8 with #topic4", 18);

    const auto trendingTopics = service->getTrendingTopics(11, 18);

    EXPECT_EQ(trendingTopics.size(), 4);
    EXPECT_EQ(trendingTopics[0], "topic2");// 3 times
    EXPECT_EQ(trendingTopics[1], "topic1");// 2 times
    EXPECT_EQ(trendingTopics[2], "topic3");// 2 times
    EXPECT_EQ(trendingTopics[3], "topic4");// 1 time
}
