#include <utility>
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include "subscriptions.h"
#include "info.h"

Cell::Cell() {}

bool Cell::getState() const { return isOn; }

Info Cell::getInfo() const {
}

void Cell::setOn() {
}

void Cell::toggle() {
}

void Cell::setCoords(int r, int c) { this->r = r; this->c = c; }

void Cell::notify(Subject &) {
}

SubscriptionType Cell::subType() const {
  return SubscriptionType::SwitchOnly;
}
