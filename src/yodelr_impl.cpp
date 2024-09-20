#include <yodelr/yodelr_impl.h>

using namespace yodelr;

void YodelrImpl::addUser(const std::string &userName) {
    mUsersToTimestamps[userName] = std::set<std::uint64_t>();
}

void YodelrImpl::addPost(const std::string &userName, const std::string &postText, std::uint64_t timestamp) {
    // TODO
}

void YodelrImpl::deleteUser(const std::string &userName) {
    // TODO
}

PostTexts YodelrImpl::getPostsForUser(const std::string &userName) const {
    // TODO
    return PostTexts();
}

PostTexts YodelrImpl::getPostsForTopic(const std::string &topic) const {
    // TODO
    return PostTexts();
}

Topics YodelrImpl::getTrendingTopics(std::uint64_t fromTimestamp, std::uint64_t toTimestamp) const {
    // TODO
    return Topics();
}
