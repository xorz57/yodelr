#include <yodelr/yodelr_impl.h>

#include <regex>

using namespace yodelr;

void YodelrImpl::addUser(const std::string &userName) {
    mUsersToTimestamps[userName] = std::set<std::uint64_t>();
}

void YodelrImpl::addPost(const std::string &userName, const std::string &postText, std::uint64_t timestamp) {
    mUsersToTimestamps[userName].insert(timestamp);
    mTimestampsToPosts[timestamp] = postText;
    for (const std::string &topic: extractTopics(postText)) {
        mTopicsToTimestamps[topic].insert(timestamp);
    }
}

void YodelrImpl::deleteUser(const std::string &userName) {
    auto it = mUsersToTimestamps.find(userName);
    if (it != mUsersToTimestamps.end()) {
        for (auto timestamp: it->second) {
            mTimestampsToPosts.erase(timestamp);
        }
    }
}

PostTexts YodelrImpl::getPostsForUser(const std::string &userName) const {
    PostTexts postTexts;
    auto it1 = mUsersToTimestamps.find(userName);
    if (it1 != mUsersToTimestamps.end()) {
        for (auto timestamp: it1->second) {
            auto it2 = mTimestampsToPosts.find(timestamp);
            if (it2 != mTimestampsToPosts.end()) {
                postTexts.push_back(it2->second);
            }
        }
    }
    return postTexts;
}

PostTexts YodelrImpl::getPostsForTopic(const std::string &topic) const {
    PostTexts postTexts;
    auto it1 = mTopicsToTimestamps.find(topic);
    if (it1 != mTopicsToTimestamps.end()) {
        for (auto timestamp: it1->second) {
            auto it2 = mTimestampsToPosts.find(timestamp);
            if (it2 != mTimestampsToPosts.end()) {
                postTexts.push_back(it2->second);
            }
        }
    }
    return postTexts;
}

Topics YodelrImpl::getTrendingTopics(std::uint64_t fromTimestamp, std::uint64_t toTimestamp) const {
    // TODO
    return Topics();
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