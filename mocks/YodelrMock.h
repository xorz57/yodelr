#pragma once

#include "Yodelr/IYodelr.h"

#include <gmock/gmock.h>

class YodelrMock : public IYodelr {
public:
    MOCK_METHOD(void, addUser, (const std::string &userName), (override));
    MOCK_METHOD(void, addPost, (const std::string &userName, const std::string &postText, std::uint64_t timestamp), (override));
    MOCK_METHOD(void, deleteUser, (const std::string &userName), (override));
    MOCK_METHOD(PostTexts, getPostsForUser, (const std::string &userName), (override));
    MOCK_METHOD(PostTexts, getPostsForTopic, (const std::string &topic) const, (override));
    MOCK_METHOD(PostTexts, getPostsForTopics, (const Topics &topics) const, (override));
    MOCK_METHOD(Topics, getTrendingTopics, (std::uint64_t fromTimestamp, std::uint64_t toTimestamp) const, (override));
};
