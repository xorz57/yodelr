#include <yodelr/yodelr_impl.h>

using namespace yodelr;

void YodelrImpl::addUser(const std::string &userName) {
    // TODO
}

void YodelrImpl::addPost(const std::string &userName, const std::string &postText, uint64_t timestamp) {
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

Topics YodelrImpl::getTrendingTopics(uint64_t fromTimestamp, uint64_t toTimestamp) const {
    // TODO
    return Topics();
}
