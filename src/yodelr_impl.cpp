#include <yodelr/yodelr_impl.h>

#include <regex>

using namespace yodelr;

void YodelrImpl::addUser(const std::string &userName) {
    mUserToTimestamps[userName] = std::set<std::uint64_t>();
}

void YodelrImpl::addPost(const std::string &userName, const std::string &postText, std::uint64_t timestamp) {
    mUserToTimestamps[userName].insert(timestamp);
    mTimestampToPost[timestamp] = postText;
    for (const std::string &topic: extractTopics(postText)) {
        mTopicToTimestamps[topic].insert(timestamp);
    }
}

void YodelrImpl::deleteUser(const std::string &userName) {
    auto it = mUserToTimestamps.find(userName);
    if (it != mUserToTimestamps.end()) {
        for (auto timestamp: it->second) {
            mTimestampToPost.erase(timestamp);
        }
    }
}

PostTexts YodelrImpl::getPostsForUser(const std::string &userName) const {
    PostTexts postTexts;
    auto it1 = mUserToTimestamps.find(userName);
    if (it1 != mUserToTimestamps.end()) {
        for (auto timestamp: it1->second) {
            auto it2 = mTimestampToPost.find(timestamp);
            if (it2 != mTimestampToPost.end()) {
                postTexts.push_back(it2->second);
            }
        }
    }
    return postTexts;
}

PostTexts YodelrImpl::getPostsForTopic(const std::string &topic) const {
    PostTexts postTexts;
    auto it1 = mTopicToTimestamps.find(topic);
    if (it1 != mTopicToTimestamps.end()) {
        for (auto timestamp: it1->second) {
            auto it2 = mTimestampToPost.find(timestamp);
            if (it2 != mTimestampToPost.end()) {
                postTexts.push_back(it2->second);
            }
        }
    }
    return postTexts;
}

Topics YodelrImpl::getTrendingTopics(std::uint64_t fromTimestamp, std::uint64_t toTimestamp) const {
    Topics topics;
    std::map<std::string, std::uint64_t> topicFrequency;
    for (auto &[topic, timestamps]: mTopicToTimestamps) {
        std::uint64_t count = 0;
        for (auto timestamp: timestamps) {
            if (timestamp >= fromTimestamp && timestamp <= toTimestamp) {
                count++;
            }
        }
        if (count > 0) {
            topicFrequency[topic] = count;
        }
    }
    std::vector<std::pair<std::string, int>> sortedTopics(topicFrequency.begin(), topicFrequency.end());
    std::sort(sortedTopics.begin(), sortedTopics.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.second > rhs.second;
    });
    for (const auto &topic: sortedTopics) {
        topics.push_back(topic.first);
    }
    return topics;
}

Topics YodelrImpl::extractTopics(const std::string &postText) {
    Topics topics;
    std::regex topicPattern(R"(\#(\w+))");
    auto wordsBegin = std::sregex_iterator(postText.begin(), postText.end(), topicPattern);
    auto wordsEnd = std::sregex_iterator();
    for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
        topics.push_back((*i)[1].str());
    }
    return topics;
}