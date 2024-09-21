#include <yodelr/yodelr.h>

#include <map>
#include <set>

namespace yodelr {
    class YodelrImpl : public Yodelr {
    public:
        void addUser(const std::string &userName) override;
        void addPost(const std::string &userName, const std::string &postText, std::uint64_t timestamp) override;
        void deleteUser(const std::string &userName) override;
        PostTexts getPostsForUser(const std::string &userName) const override;
        PostTexts getPostsForTopic(const std::string &topic) const override;
        Topics getTrendingTopics(std::uint64_t fromTimestamp, std::uint64_t toTimestamp) const override;

    private:
        static Topics extractTopics1(const std::string &postText);
        static Topics extractTopics2(const std::string &postText);

        std::map<std::uint64_t, std::string, std::less<std::uint64_t>> mTimestampToPostText;
        std::map<std::string, std::set<std::uint64_t>> mTopicToTimestamps;
        std::map<std::string, std::set<std::uint64_t>> mUserToTimestamps;
    };
}// namespace yodelr