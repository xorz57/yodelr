#include <Yodelr/Yodelr.h>

#include <cstdlib>
#include <iostream>
#include <memory>

static void printPosts(const yodelr::PostTexts &postTexts, const std::string &label) {
    std::cout << label << ": [\n";
    for (const auto &postText: postTexts) {
        std::cout << "\t" << postText << ",\n";
    }
    std::cout << "]\n";
}

static void printTopics(const yodelr::Topics &topics, const std::string &label) {
    std::cout << label << ": [\n";
    for (const auto &topic: topics) {
        std::cout << "\t" << topic << ",\n";
    }
    std::cout << "]\n";
}

int main() {
    std::unique_ptr<yodelr::IYodelr> service = std::make_unique<yodelr::Yodelr>();
    if (!service) {
        return EXIT_FAILURE;
    }

    service->addUser("john");

    try {
        service->addPost("john", "just #chilling today", 1);
        service->addPost("john", "eating #steak for dinner", 2);
        service->addPost("john", "ugh! this #steak tasted like dog food", 3);
    } catch (const std::length_error &e) {
        std::cerr << e.what() << "\n";
    }

    const auto postTexts1 = service->getPostsForUser("john");
    const auto postTexts2 = service->getPostsForTopic("steak");
    const auto postTexts3 = service->getPostsForTopics({"chilling", "steak"});

    const auto topics1 = service->getTrendingTopics(1, 3);
    const auto topics2 = service->getTrendingTopics(2, 3);

    printPosts(postTexts1, "postTexts1");
    printPosts(postTexts2, "postTexts2");
    printPosts(postTexts3, "postTexts3");

    printTopics(topics1, "topics1");
    printTopics(topics2, "topics2");

    return EXIT_SUCCESS;
}
