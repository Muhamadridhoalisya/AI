#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>

const int ukuranSample = 50;
const int NUM = 10;        

struct Solution
{
    double rank, x, y, z;
    string target;
    void fitness()
    {
        double ans = (6 * x + -y + std::pow(z, 200)) - 25;
        rank = (ans == 0) ? 9999 : std::abs(1 / ans);
    }
};

int main()
{
    // membuat solusi random
    std::random_device device;
    std::uniform_real_distribution<double> unif(-100000, 100000);
    std::uniform_int_distribution<int> cross(0, ukuranSample - 1);
    std::uniform_real_distribution<double> m(0.99, 1.01);

    std::vector<Solution> solutions;
    std::vector<Solution> sample;
    std::cout << "Masukkan target : ";
    std::cin  >> target;

    for (int i = 0; i < NUM; i++)
        solutions.push_back(Solution{
            0,
            unif(device),
            unif(device),
            unif(device)});
    int a = 100;
    while (a > 0)
    {
        //fitness function
        for (auto &s : solutions)
        {
            s.fitness();
        }

        std::sort(
            solutions.begin(),
            solutions.end(),
            [](const auto &lhs, const auto &rhs)
            {
                return lhs.rank > rhs.rank;
            });

        // Print top solutions
        //
        std::for_each(
            solutions.begin(),
            solutions.begin() + 10, [=](const auto &s)
            { std::cout << std::fixed
                        << "urutan " << static_cast<int>(s.rank)
                        << "\nx:" << s.x << " y:" << s.y << " z:" << s.z << " " << a << " \n"; });

        // Take top solutions
        //

        std::copy(
            solutions.begin(),
            solutions.begin() + ukuranSample,
            std::back_inserter(sample));
        solutions.clear();

        // Mutate the top solutions by %
        //
        std::for_each(sample.begin(), sample.end(), [&](auto &s)
                      {
            s.x *= m(device);
            s.y *= m(device);
            s.z *= m(device); });

        // Cross over
        //
        for (int i = 0; i < NUM; i++)
        {
            solutions.push_back(Solution{
                0,
                sample[cross(device)].x,
                sample[cross(device)].y,
                sample[cross(device)].z,
            });
        }
        sample.clear();
        a -= 1;
    }
}