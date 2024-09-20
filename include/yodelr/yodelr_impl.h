#include <yodelr/yodelr.h>

namespace yodelr {
    class YodelrImpl : public Yodelr {
    public:
        void addUser(const std::string &userName) override;
        void addPost(const std::string &userName, const std::string &postText, uint64_t timestamp) override;
        void deleteUser(const std::string &userName) override;
        PostTexts getPostsForUser(const std::string &userName) const override;
        PostTexts getPostsForTopic(const std::string &topic) const override;
        Topics getTrendingTopics(uint64_t fromTimestamp, uint64_t toTimestamp) const override;
    };
}// namespace yodelr