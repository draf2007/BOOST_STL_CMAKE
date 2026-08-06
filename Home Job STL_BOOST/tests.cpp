#define BOOST_TEST_MODULE WordFreqTests

#include <boost/test/included/unit_test.hpp>

#define WORDFREQ_TESTS

#include "main.cpp"

BOOST_AUTO_TEST_CASE(test_tokenize_basic) {
    std::string text = "Hello, world! Test.";
    auto words = tokenize(text);

    BOOST_CHECK_EQUAL(words.size(), 3u);
    BOOST_CHECK_EQUAL(words[0], "hello");
    BOOST_CHECK_EQUAL(words[1], "world");
    BOOST_CHECK_EQUAL(words[2], "test");
}

BOOST_AUTO_TEST_CASE(test_tokenize_empty) {
    std::string text = "";
    auto words = tokenize(text);
    BOOST_CHECK_EQUAL(words.size(), 0u);
}

BOOST_AUTO_TEST_CASE(test_tokenize_only_delimiters) {
    std::string text = "   ,,, ... !!!   ";
    auto words = tokenize(text);
    BOOST_CHECK_EQUAL(words.size(), 0u);
}

BOOST_AUTO_TEST_CASE(test_tolower) {
    BOOST_CHECK_EQUAL(toLower("Hello"), "hello");
    BOOST_CHECK_EQUAL(toLower("WORLD"), "world");
    BOOST_CHECK_EQUAL(toLower("already"), "already");
    //BOOST_CHECK_EQUAL(toLower(""), "");
}

BOOST_AUTO_TEST_CASE(test_filter_stop_words) {
    std::vector<std::string> words = {"hello", "world", "the", "a", "test"};
    std::set<std::string> stopWords = {"the", "a"};

    auto filtered = filterStopWords(words, stopWords);

    BOOST_CHECK_EQUAL(filtered.size(), 3u);
    BOOST_CHECK_EQUAL(filtered[0], "hello");
    BOOST_CHECK_EQUAL(filtered[1], "world");
    BOOST_CHECK_EQUAL(filtered[2], "test");
}

BOOST_AUTO_TEST_CASE(test_filter_no_stop_words) {
    std::vector<std::string> words = {"hello", "world"};
    std::set<std::string> stopWords = {"the", "a"};

    auto filtered = filterStopWords(words, stopWords);

    BOOST_CHECK_EQUAL(filtered.size(), 2u);
}

BOOST_AUTO_TEST_CASE(test_count_word) {
    std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    auto freq = countWord(words);

    BOOST_CHECK_EQUAL(freq.size(), 3u);
    BOOST_CHECK_EQUAL(freq["apple"], 3);
    BOOST_CHECK_EQUAL(freq["banana"], 2);
    BOOST_CHECK_EQUAL(freq["cherry"], 1);
}

BOOST_AUTO_TEST_CASE(test_count_word_empty) {
    std::vector<std::string> words;
    auto freq = countWord(words);
    BOOST_CHECK_EQUAL(freq.size(), 0u);
}

BOOST_AUTO_TEST_CASE(test_sort_by_freq) {
    std::map<std::string, int> freq = {
        {"apple", 3},
        {"banana", 1},
        {"cherry", 2}
    };

    auto sorted = sortByFreq(freq);

    BOOST_CHECK_EQUAL(sorted.size(), 3u);
    // Первое слово должно быть с наибольшей частотой
    BOOST_CHECK_EQUAL(sorted[0].first, "apple");
    BOOST_CHECK_EQUAL(sorted[0].second, 3);
    // Второе — со средней частотой
    BOOST_CHECK_EQUAL(sorted[1].first, "cherry");
    BOOST_CHECK_EQUAL(sorted[1].second, 2);
    // Третье — с наименьшей частотой
    BOOST_CHECK_EQUAL(sorted[2].first, "banana");
    BOOST_CHECK_EQUAL(sorted[2].second, 1);
}