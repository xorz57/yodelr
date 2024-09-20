#include <yodelr/yodelr_impl.h>

#include <cstdlib>
#include <iostream>

int main() {
    yodelr::Yodelr *service = new yodelr::YodelrImpl;
    if (service == nullptr) {
        return EXIT_FAILURE;
    }

    service->addUser("john");
    service->addPost("john", "just #chilling today", 1);
    service->addPost("john", "eating #steak for dinner", 2);
    service->addPost("john", "ugh! this #steak tasted like dog food", 3);

    auto postsTexts1 = service->getPostsForUser("john");
    for (const auto &postText: postsTexts1) {
        std::cout << postText << "\n";
    }

    auto postTexts2 = service->getPostsForTopic("steak");
    for (const auto &postText: postTexts2) {
        std::cout << postText << "\n";
    }

    auto topics1 = service->getTrendingTopics(1, 3);
    for (const auto &topic: topics1) {
        std::cout << topic << "\n";
    }

    auto topics2 = service->getTrendingTopics(2, 3);
    for (const auto &topic: topics2) {
        std::cout << topic << "\n";
    }

    delete service;

    return EXIT_SUCCESS;
}