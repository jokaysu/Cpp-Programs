//
//  seansort.cpp
//
//  Created by c28su on 2017-01-30.
//  Copyright © 2017 c28su. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>

int partition(std::vector<double> & vec, int x, int y, int t) {
    double temp = vec[x];
    vec[x] = vec[t];
    vec[t] = temp;
    int i = x + 1;
    int j = y;
    while (true) {
        while (i < y + 1 && vec[i] <= vec[x])
            i++;
        while (j >= x + 1 && vec[j] > vec[x])
            j--;
        if (j < i)
            break;
        else {
            temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
    }
    temp = vec[x];
    vec[x] = vec[j];
    vec[j] = temp;
    return j;
}

void seanSort(std::vector<double> & vec, int x, int y) {
    int total = y - x + 1;
    if (total <= 1) return;
    double p = 0;
    for (int i = x; i <= y; ++i)
        p += vec[i];
    p = p / double(total);
    int t = x;
    int diff = std::abs(p - vec[x]);
    for (int i = x; i <= y; ++i)
        if (std::abs(vec[i] - p) < diff) {
            t = i;
            diff = std::abs(vec[i] - p);
        }
//    std::cout << "x = " << x << std::endl;
//    std::cout << "y = " << y << std::endl;
//    std::cout << "p = " << p << std::endl;
//    std::cout << "t = " << t << std::endl;
//    for (int i = x; i <= y; ++i)
//        std::cout << vec[i] << " ";
//    std::cout << std::endl;
    t = partition(vec, x, y, t);
//    std::cout << "t2 = " << t << std::endl;
    seanSort(vec, x, t - 1);
    seanSort(vec, t + 1, y);
}

int main(int argc, const char * argv[]) {
    int n;
    double r;
    std::cin >> n;
    std::vector<double> v;
    for (int i = 0; i < n; ++i) {
        std::cin >> r;
        v.push_back(r);
    }
    seanSort(v, 0, n - 1);
    for (int i = 0; i < n; ++i)
        std::cout << v[i] << std::endl;
    return 0;
}
