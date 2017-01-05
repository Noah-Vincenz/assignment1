#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
using std::vector;
using std::string;
using std::ostream;

class Item {
private:
    double latitude;
    double longitude;
    string ID;
    int timeAvailable;
    friend ostream& operator<< (ostream&, Item const&);
    bool hasBeenVisited;

public:
    Item(double latitudeIn, double longitudeIn, string IDIn, int timeAvailableIn)
            : latitude(latitudeIn),
              longitude(longitudeIn),
              ID(IDIn),
              timeAvailable(timeAvailableIn),
              hasBeenVisited(false) {
    }
    double const distanceTo(const Item &anotherItem) {
        double dlon = convertToRadians(anotherItem.longitude) - convertToRadians(longitude);
        double dlat = convertToRadians(anotherItem.latitude) - convertToRadians(latitude);
        double a = pow((sin(dlat/2)), 2) + cos(convertToRadians(latitude)) * cos(convertToRadians(anotherItem.latitude)) * pow((sin(dlon/2)), 2);
        double c = 2 * atan2( sqrt(a), sqrt(1-a) );
        return 6373000 * c;
    }
    double const convertToRadians(double d) {
        return d * (M_PI / 180);
    }
    double getTimeAvailable()const {
        return timeAvailable;
    }
    void setVisited(bool b) {
        hasBeenVisited = b;
    }
    bool const getVisited() {
        return hasBeenVisited;
    }
    bool operator==(Item otherItem) {
        return (longitude == otherItem.longitude && latitude == otherItem.latitude && ID == otherItem.ID && timeAvailable == otherItem.timeAvailable);
    }
    friend ostream& operator<< (ostream &outString, Item const &itemIn) {
        outString << "{" << itemIn.latitude << ", " ;
        outString << itemIn.longitude << ", " ;
        outString << "\"" << itemIn.ID << "\"" << ", " ;
        outString << itemIn.timeAvailable << "}" ;
        return outString ;
    }
};

class MapOfItems {
private:
    vector<Item> itemVector;

public:
    void addItem(Item itemIn) {
        itemVector.push_back(itemIn);
    }
    std::size_t const size() {
        return itemVector.size();
    }
    vector<Item> const getTour(double walkingSpeed) {
        vector<Item> journeyVector;
        for (int i = 0; i < itemVector.size(); ++i) {
            itemVector.at(i).setVisited(false);
        }
        journeyVector.push_back(itemVector.at(0)); //first element of itemVector always first destination
        double currentTime = journeyVector.at(0).getTimeAvailable();
        itemVector.at(0).setVisited(true);
        Item itemToBeAdded(itemVector.at(0));
        double shortestTime;
        int indexOfItemVectorItem = 0;
        int indexToBeVisited = 0;
        double distanceToI = 0;
        double timeTaken;
        while (currentTime < 3600) {
            double visitI = 0;
            if  (journeyVector.size() == itemVector.size()) {
                break;
            }
            shortestTime = 3600;
            for (int i2 = 0; i2 < itemVector.size(); ++i2) { //comparing distance of journeyVector0 to all items left in intemVector
                timeTaken = 0;
                distanceToI = itemVector.at(indexOfItemVectorItem).distanceTo(itemVector.at(i2));
                if (itemVector.at(i2).getVisited() == false) {
                    if ((distanceToI / walkingSpeed) + currentTime < itemVector.at(i2).getTimeAvailable()) {
                        timeTaken = itemVector.at(i2).getTimeAvailable();
                    } else if ((distanceToI / walkingSpeed) + currentTime > itemVector.at(i2).getTimeAvailable() + 900) {
                        continue;
                    } else {
                        timeTaken = (distanceToI / walkingSpeed) + currentTime;
                    }
                    if (timeTaken < shortestTime) {
                        shortestTime = timeTaken;
                        itemToBeAdded = itemVector.at(i2);
                        indexToBeVisited = i2;
                    }
                    visitI = shortestTime;
                }
            }
            if (itemToBeAdded == itemVector.at(indexOfItemVectorItem)) {
                break;
            } else{
                journeyVector.push_back(itemToBeAdded); //only do those if there is an item
                itemVector.at(indexToBeVisited).setVisited(true);
                currentTime = visitI;
                indexOfItemVectorItem = indexToBeVisited;
            }
        }
        return journeyVector;
    }
};
// don't write any code below this line

#endif

