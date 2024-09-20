#include <yodelr/yodelr_impl.h>

#include <cstdlib>
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<yodelr::Yodelr> service = std::make_unique<yodelr::YodelrImpl>();
    if (!service) {
        return EXIT_FAILURE;
    }

    service->addUser("john");

    service->addPost("john", "just #chilling today", 1);
    service->addPost("john", "eating #steak for dinner", 2);
    service->addPost("john", "ugh! this #steak tasted like dog food", 3);

    auto postsTexts1 = service->getPostsForUser("john");
    std::cout << "postsTexts1: [\n";
    for (const auto &postText: postsTexts1) {
        std::cout << "\t" << postText << ",\n";
    }
    std::cout << "]\n";

    auto postTexts2 = service->getPostsForTopic("steak");
    std::cout << "postsTexts2: [\n";
    for (const auto &postText: postTexts2) {
        std::cout << "\t" << postText << ",\n";
    }
    std::cout << "]\n";

    auto topics1 = service->getTrendingTopics(1, 3);
    std::cout << "topics1: [\n";
    for (const auto &topic: topics1) {
        std::cout << topic << "\n";
    }
    std::cout << "]\n";

    auto topics2 = service->getTrendingTopics(2, 3);
    std::cout << "topics2: [\n";
    for (const auto &topic: topics2) {
        std::cout << topic << "\n";
    }
    std::cout << "]\n";

    return EXIT_SUCCESS;
}