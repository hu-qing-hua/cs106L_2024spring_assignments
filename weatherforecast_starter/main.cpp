/*
Assignment 4: Weather Forecast

This assignment works with template functions and lambdas to become the best weather forecaster
at the Stanford Daily. Be sure to read the assignment details in the PDF.

Submit to Paperless by 11:59pm on 5/10/2024.
*/

// TODO: import anything from the STL that might be useful!
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

// TODO: write convert_f_to_c function here. Remember it must be a template function that always returns
// a double.
// [function definition here]
template <typename Input>
double convert_f_to_c(Input Fah)
{
    return (static_cast<double>(Fah) - 32) * 5.0 / 9;
}

template <typename Function>
std::vector<double> get_forecast(std::vector<std::vector<double>> readings, Function fn)
{
    // TODO: write get_forecast here!
    std::vector<double> result;
    result.reserve(readings.size());
    for (const auto &daily_readings : readings)
    {
        result.push_back(fn(daily_readings));
    }
    return result;
}

int main()
{
    std::vector<std::vector<double>> readings = {
        {70, 75, 80, 85, 90},
        {60, 65, 70, 75, 80},
        {50, 55, 60, 65, 70},
        {40, 45, 50, 55, 60},
        {30, 35, 40, 45, 50},
        {50, 55, 61, 65, 70},
        {40, 45, 50, 55, 60}};

    // TODO: Convert temperatures to Celsius and output to output.txt
    std::ofstream outputFile("output.txt");
    if (outputFile.is_open())
    {
        outputFile << "Convert temperatures to Celsius\n";
        for (const auto &daily_reading : readings)
        {
            std::vector<double> daily_celsius(daily_reading.size());
            std::transform(daily_reading.begin(), daily_reading.end(), daily_celsius.begin(), convert_f_to_c<double>);
            for (const auto &data : daily_celsius)
            {
                outputFile << data << " ";
            }
            outputFile << "\n";
        }
        outputFile.close();
    }
    else
    {
        std::cerr << "error opening file\n";
    }

    // TODO: Find the maximum temperature for each day and output to output.txt
    outputFile.open("output.txt", std::ios::app);
    if (outputFile.is_open())
    {
        outputFile << "\nthe maximum temperature for each day\n";
        auto max_fn = [](const std::vector<double> &daily_reading)
        {
            return *std::max_element(daily_reading.begin(), daily_reading.end());
        };
        std::vector<double> dailyMaxs;
        dailyMaxs = get_forecast(readings, max_fn);
        for (const auto &data : dailyMaxs)
        {
            outputFile << data << " ";
        }
        outputFile.close();
    }
    else
    {
        std::cerr << "error opening file\n";
    }

    // TODO: Find the minimum temperature for each day and output to output.txt
    outputFile.open("output.txt", std::ios::app);
    if (outputFile.is_open())
    {
        outputFile << "\nthe minimum temperature for each day\n";
        auto min_fn = [](const std::vector<double> &daily_reading)
        {
            return *std::min_element(daily_reading.begin(), daily_reading.end());
        };
        std::vector<double> dailyMins;
        dailyMins = get_forecast(readings, min_fn);
        for (const auto &data : dailyMins)
        {
            outputFile << data << " ";
        }
        outputFile.close();
    }
    else
    {
        std::cerr << "error opening file\n";
    }

    // TODO: Find the average temperature for each day and output to output.txt
    outputFile.open("output.txt", std::ios::app);
    if (outputFile.is_open())
    {
        outputFile << "\nthe average temperature for each day\n";
        auto aver_fn = [](const std::vector<double> &daily_reading)
        {
            double sum = std::accumulate(daily_reading.begin(), daily_reading.end(), 0.0);
            return sum / daily_reading.size();
        };
        std::vector<double> dailyAvers;
        dailyAvers = get_forecast(readings, aver_fn);
        for (const auto &data : dailyAvers)
        {
            outputFile << data << " ";
        }
        outputFile.close();
    }
    else
    {
        std::cerr << "error opening file\n";
    }
    return 0;
}

// std::transform
//  https://www.geeksforgeeks.org/transform-c-stl-perform-operation-elements/
//  std::max_element 是返回一个指针
//  https://cplusplus.com/reference/algorithm/max_element/