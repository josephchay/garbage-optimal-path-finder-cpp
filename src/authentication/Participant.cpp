#include "Participant.h"

namespace authentication {
    Participant::Participant(int id, const std::string& username, const std::string& password, const std::string& fullName, std::string & discountPoints)
            : id(id), username(username), password(password), fullName(fullName), discountPoints(discountPoints) {}

    int Participant::getId() const { return id; }
    std::string Participant::getUsername() const { return username; }
    std::string Participant::getPassword() const { return password; }
    std::string Participant::getFullName() const { return fullName; }
    std::string Participant::getDiscountPoints() const { return discountPoints; }

    void Participant::setDiscountCount(std::string &newDiscountCount) {
        discountPoints = newDiscountCount;
    }
}
