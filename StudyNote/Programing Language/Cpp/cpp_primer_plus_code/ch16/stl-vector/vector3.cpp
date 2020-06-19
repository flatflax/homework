//
//  vector3.cpp
//  cpp_primer_plus
//
//  Created by 須木 on 2020/6/18.
//  Copyright © 2020 須木. All rights reserved.
//


// vect3.cpp -- using STL functions
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
struct Review {
    std::string title; int rating;
};
bool operator<(const Review & r1, const Review & r2);
bool worseThan(const Review & r1, const Review & r2);
bool FillReview_2(Review & rr);
void ShowReview_2(const Review & rr);


int ch16_vect_stl_func_main() {
    using namespace std;
    vector<Review> books;
    Review temp;
    
    while (FillReview_2(temp))
        books.push_back(temp);
    cout << "Thank you. You entered the following "
        << books.size() << " ratings:\n" << "Rating\tBook\n";
    for_each(books.begin(), books.end(), ShowReview_2);
    
    sort(books.begin(), books.end());
    cout << "Sorted by title:\nRating\tBook\n";
    for_each(books.begin(), books.end(), ShowReview_2);
    
    sort(books.begin(), books.end(), worseThan);
    cout << "Sorted by rating:\nRating\tBook\n";
    for_each(books.begin(), books.end(), ShowReview_2);
    
    random_shuffle(books.begin(), books.end());
    cout << "After shuffling:\nRating\tBook\n";
    for_each(books.begin(), books.end(), ShowReview_2);
    
    cout << "Bye.\n";
    return 0;
}

bool operator<(const Review & r1, const Review & r2) {
    if (r1.title < r2.title)
        return true;
    else if (r1.title == r2.title && r1.rating < r2.rating)
        return true;
    else
        return false;
}

bool worseThan(const Review & r1, const Review & r2) {
    if (r1.rating < r2.rating)
        return true;
    else
        return false;
}

bool FillReview_2(Review & rr)
{
    std::cout << "Enter book title (quit to quit): ";
    std::getline(std::cin,rr.title);
    if (rr.title == "quit")
        return false;
    
    std::cout << "Enter book rating: ";
    std::cin >> rr.rating;
    if (!std::cin)
        return false;
    
    std::cin.get();
    return true;
    
}

void ShowReview_2(const Review & rr)
{
    std::cout << rr.rating << "\t" << rr.title << std::endl;
}
