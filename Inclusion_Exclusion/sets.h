#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

enum Operation {
    INTERSECTION,
    UNION
};

enum class Topic {
    MATH,
    SCIENCE,
    HISTORY,
    ART,
    TECHNOLOGY,
    LANGUAGE,
    LITERATURE,
    MUSIC,
    PHILOSOPHY,
    RELIGION,
    CULTURE,
    GEOGRAPHY,
    POLITICS,
    ECONOMICS,
    ENGINEERING,
    MEDICINE,
    PSYCHOLOGY,
    SOCIOLOGY,
    ENVIRONMENT,
    LAW,
    BUSINESS
};

enum GroupType {
    Teachers,
	Students
};

class sets {
public:
    std::set<int> elements;
    std::string name;
	Topic topic;
	GroupType groupType;



    void createSetWithOptionalOverlap(const std::string& setName,
        int lowerBound,
        int upperBound,
        int confidence,
        GroupType type,
        const sets* otherSet = nullptr,
        double overlapChance = 0.9)
    {
        this->name = setName;
        this->groupType = type;
        elements.clear();

        if (lowerBound > upperBound) std::swap(lowerBound, upperBound); // safe range

        int minSize = 5;
        int maxSize = 20;
        int targetSize = minSize + (confidence * (maxSize - minSize) / 50);

        int maxUnique = upperBound - lowerBound + 1;
        if (targetSize > maxUnique) targetSize = maxUnique;

        if (targetSize <= 0) targetSize = 1; // ensure at least 1 element

        while ((int)elements.size() < targetSize) {
            int num = lowerBound + (rand() % (upperBound - lowerBound + 1));
            elements.insert(num);
        }

        // Optionally add 1 element from otherSet to ensure some overlap
        if (otherSet && !otherSet->elements.empty() &&
            ((rand() % 100) < static_cast<int>(overlapChance * 100)))
        {
            auto it = otherSet->elements.begin();
            std::advance(it, rand() % otherSet->elements.size());
            elements.insert(*it);
        }
    }



    void displaySet() const {
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
    }

    std::set<int> getIntersection(const sets& otherSet) const {
        std::set<int> result;

        for (const auto& elem : elements) {
            if (otherSet.elements.count(elem)) {
                result.insert(elem);
            }
        }
        return result;
    }

    std::set<int> getUnion(const sets& otherSet) const {
        std::set<int> result = elements; // start with this set

        for (const auto& elem : otherSet.elements) {
            result.insert(elem); // set insert automatically avoids duplicates
        }

        return result;
    }

    std::string getTopicString() const {
        switch (topic) {
            case Topic::MATH: return "Math";
            case Topic::SCIENCE: return "Science";
            case Topic::HISTORY: return "History";
            case Topic::ART: return "Art";
            case Topic::TECHNOLOGY: return "Technology";
            case Topic::LANGUAGE: return "Language";
            case Topic::LITERATURE: return "Literature";
            case Topic::MUSIC: return "Music";
            case Topic::PHILOSOPHY: return "Philosophy";
            case Topic::RELIGION: return "Religion";
            case Topic::CULTURE: return "Culture";
            case Topic::GEOGRAPHY: return "Geography";
            case Topic::POLITICS: return "Politics";
            case Topic::ECONOMICS: return "Economics";
            case Topic::ENGINEERING: return "Engineering";
            case Topic::MEDICINE: return "Medicine";
            case Topic::PSYCHOLOGY: return "Psychology";
            case Topic::SOCIOLOGY: return "Sociology";
            case Topic::ENVIRONMENT: return "Environment";
            case Topic::LAW: return "Law";
            case Topic::BUSINESS: return "Business";
            default: return "Unknown";
        }
	}
    int getSize() const { return static_cast<int>(elements.size()); }


    std::string getGroupTypeString() const {
        return (groupType == GroupType::Teachers) ? "Teachers" : "Students";
	}
};
