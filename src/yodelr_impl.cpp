#include <yodelr/yodelr_impl.h>

#include <ranges>
#include <stdexcept>

using namespace yodelr;

void YodelrImpl::addUser(const std::string &userName) {
    mUserToTimestamps[userName] = {};
}

void YodelrImpl::addPost(const std::string &userName, const std::string &postText, std::uint64_t timestamp) {
    if (postText.length() > 140) {
        throw std::length_error("post text exceeds the 140-character limit");
    }

    mUserToTimestamps[userName].insert(timestamp);
    mTimestampToPostText[timestamp] = postText;
    for (const auto &topic: YodelrImpl::extractTopics(postText)) {
        mTopicToTimestamps[topic].insert(timestamp);
    }
}

void YodelrImpl::deleteUser(const std::string &userName) {
    const auto it = mUserToTimestamps.find(userName);
    if (it != mUserToTimestamps.end()) {
        for (const auto timestamp: it->second) {
            mTimestampToPostText.erase(timestamp);
            for (auto &timestamps: std::views::values(mTopicToTimestamps)) {
                timestamps.erase(timestamp);
            }
        }
        mUserToTimestamps.erase(it);
    }
}

PostTexts YodelrImpl::getPostsForUser(const std::string &userName) const {
    PostTexts postTexts;
    const auto it1 = mUserToTimestamps.find(userName);
    if (it1 != mUserToTimestamps.end()) {
        for (auto timestamp: it1->second) {
            const auto it2 = mTimestampToPostText.find(timestamp);
            if (it2 != mTimestampToPostText.end()) {
                postTexts.push_back(it2->second);
            }
        }
    }
    return postTexts;
}

PostTexts YodelrImpl::getPostsForTopic(const std::string &topic) const {
    PostTexts postTexts;
    const auto it1 = mTopicToTimestamps.find(topic);
    if (it1 != mTopicToTimestamps.end()) {
        for (auto timestamp: it1->second) {
            const auto it2 = mTimestampToPostText.find(timestamp);
            if (it2 != mTimestampToPostText.end()) {
                postTexts.push_back(it2->second);
            }
        }
    }
    return postTexts;
}

Topics YodelrImpl::getTrendingTopics(std::uint64_t fromTimestamp, std::uint64_t toTimestamp) const {
    Topics topics;
    std::multimap<std::uint64_t, std::string, std::greater<>> topicFrequency;
    for (const auto &[topic, timestamps]: mTopicToTimestamps) {
        std::uint64_t count = 0;
        for (const auto timestamp: timestamps) {
            if (timestamp >= fromTimestamp && timestamp <= toTimestamp) {
                count++;
            }
        }
        bool flag = false;
        const auto range = topicFrequency.equal_range(count);
        for (auto hint = range.first; hint != range.second; ++hint) {
            if (topic < hint->second) {
                if (count > 0) {
                    topicFrequency.emplace_hint(hint, count, topic);
                    flag = true;
                    break;
                }
            }
        }
        if (!flag) {
            if (count > 0) {
                topicFrequency.emplace(count, topic);
            }
        }
    }
    for (const auto &topic: std::views::values(topicFrequency)) {
        topics.push_back(topic);
    }
    return topics;
}

Topics YodelrImpl::extractTopics(const std::string &postText) {
    Topics topics;
    std::string topic;
    bool flag = false;
    for (const char c: postText) {
        if (c == '#') {
            flag = true;
            topic.clear();
        } else if (flag && (isalnum(c) || c == '_')) {
            topic += c;
        } else if (flag) {
            if (!topic.empty()) {
                topics.push_back(topic);
            }
            flag = false;
        }
    }
    if (flag && !topic.empty()) {
        topics.push_back(topic);
    }
    return topics;
}