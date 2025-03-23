#pragma once

#include "yodelr/yodelr.h"

#include <map>
#include <set>
#include <unordered_map>

namespace yodelr {
    class YodelrImpl : public Yodelr {
    public:
        void addUser(const std::string &userName) override;
        void addPost(const std::string &userName, const std::string &postText, std::uint64_t timestamp) override;
        void deleteUser(const std::string &userName) override;
        PostTexts getPostsForUser(const std::string &userName) const override;
        PostTexts getPostsForTopic(const std::string &topic) const override;
        PostTexts getPostsForTopics(const Topics &topics) const;
        Topics getTrendingTopics(std::uint64_t fromTimestamp, std::uint64_t toTimestamp) const override;

    private:
        static Topics extractTopics(const std::string &postText);

        std::map<std::uint64_t, std::string, std::greater<>> mTimestampToPostText;
        std::map<std::string, std::set<std::uint64_t, std::greater<>>> mTopicToTimestamps;
        std::unordered_map<std::string, std::set<std::uint64_t, std::greater<>>> mUserNameToTimestamps;
    };
}// namespace yodelr
