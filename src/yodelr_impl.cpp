#include <yodelr/yodelr_impl.h>

#include <ranges>

using namespace yodelr;

const std::regex YodelrImpl::sTopicRegex(R"(\#([0-9a-zA-Z_]+))");

void YodelrImpl::addUser(const std::string &userName) {
    mUserToTimestamps[userName] = {};
}

void YodelrImpl::addPost(const std::string &userName, const std::string &postText, std::uint64_t timestamp) {
    mUserToTimestamps[userName].insert(timestamp);
    mTimestampToPostText[timestamp] = postText;
    for (const std::string &topic: YodelrImpl::extractTopicsWithoutRegex(postText)) {
        mTopicToTimestamps[topic].insert(timestamp);
    }
}

void YodelrImpl::deleteUser(const std::string &userName) {
    const auto it = mUserToTimestamps.find(userName);
    if (it != mUserToTimestamps.end()) {
        for (auto timestamp: it->second) {
            mTimestampToPostText.erase(timestamp);
        }
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
            if (timestamp > toTimestamp) break;
            if (timestamp >= fromTimestamp && timestamp <= toTimestamp) {
                count++;
            }
        }
        topicFrequency.emplace(count, topic);
    }
    for (const auto &topic: std::views::values(topicFrequency)) {
        topics.push_back(topic);
    }
    return topics;
}

Topics YodelrImpl::extractTopicsWithRegex(const std::string &postText) {
    Topics topics;
    const auto topicsBegin = std::sregex_iterator(postText.begin(), postText.end(), sTopicRegex);
    const auto topicsEnd = std::sregex_iterator();
    for (auto i = topicsBegin; i != topicsEnd; ++i) {
        topics.push_back((*i)[1].str());
    }
    return topics;
}

Topics YodelrImpl::extractTopicsWithoutRegex(const std::string &postText) {
    Topics topics;
    std::string topic;
    bool inTopic = false;
    for (const char i : postText) {
        if (i == '#') {
            inTopic = true;
            topic.clear();
        } else if (inTopic && (isalnum(i) || i == '_')) {
            topic += i;
        } else if (inTopic) {
            if (!topic.empty()) {
                topics.push_back(topic);
            }
            inTopic = false;
        }
    }
    if (inTopic && !topic.empty()) {
        topics.push_back(topic);
    }
    return topics;
}