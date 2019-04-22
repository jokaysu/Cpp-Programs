#include "Group.h"
#include <iostream>

Group::Group(const std::string & name) {
    gn = name;
    eNode = nullptr;
    gNode = nullptr;
}

Group::~Group() {/*
                  GroupNode *tem = gNode;
                  GroupNode *temtem;
                  while(tem->next) {
                  temtem = tem;
                  tem = tem->next;
                  delete temtem->gp;
                  delete temtem;
                  }
                  delete tem->gp;
                  delete tem;
                  EmailNode *tem2 = eNode;
                  EmailNode *temtem2;
                  while(tem2->next != nullptr) {
                  temtem2 = tem2;
                  tem2 = tem2->next;
                  delete temtem2;
                  }
                  delete tem2;
                  */
    if (this->gNode) delete this->gNode;
    if (this->eNode) delete this->eNode;
}
//to do

std::string Group::name() const {
    return gn;
}

std::string Group::emails() const {
    EmailNode *it = eNode->next;
    std::string ans = eNode->address();
    while(it) {
        ans = ans + ", " + it->address();
        it = it->next;
    }
    return ans;
}

void Group::addGroup( Group *g ) {
    if (gNode == nullptr) {
        gNode = new GroupNode(g);
    } else if (g->gn < gNode->gp->gn) {
        GroupNode *tem = new GroupNode(g);
        tem->next = gNode;
        gNode = tem;
    } else{
        GroupNode *tem = new GroupNode(g);
        gNode->addGroup(tem);
    }
}

void Group::addAddress( const std::string &s ) {
    if (eNode == nullptr) {
        eNode = new EmailNode(s);
    } else {
        if (s < eNode->email) {
            EmailNode *tem = new EmailNode(s);
            tem->next = eNode;
            eNode = tem;
        } else {
            eNode->addAddress(s);
        }
    }
}

bool Group::removeGroup( const std::string &s ) {
    if (gNode == nullptr || s == gn) return false;
    if (s == gNode->group()->gn) {
        GroupNode *tem = gNode;
        gNode = gNode->next;
        tem->next = nullptr;
        delete tem;
        return true;
    }
    return gNode->removeGroup(s);
}

bool Group::removeAddress( const std::string &s ) {
    if (s == eNode->email) {
        EmailNode *tem = eNode;
        eNode = eNode->next;
        tem->next = nullptr;
        delete tem;
        return true;
    }
    bool result = eNode->removeAddress(s);
    if (result) return true;
    else return gNode->removeAddress(s);
}

Group::EmailNode::EmailNode( const std::string &s ) {
    email = s;
    next = nullptr;
}

Group::EmailNode::~EmailNode() {/*
                                 EmailNode *tem = this;
                                 EmailNode *temtem;
                                 while(tem->next != nullptr) {
                                 temtem = tem;
                                 tem = tem->next;
                                 delete temtem;
                                 }
                                 delete tem;*/
    if(this->next) delete this->next;
}

void Group::EmailNode::addAddress( const std::string &s ) {
    EmailNode *tem = new EmailNode(s);
    EmailNode *it = this;
    while (it->next && s > it->next->address()) it = it->next;
    if (it->next == nullptr) it->next = tem;
    else {
        tem->next = it->next;
        it->next = tem;
    }
}

bool Group::EmailNode::removeAddress( const std::string &s ) {
    EmailNode *tem = this;
    EmailNode *it = this;
    while (it->next && s != it->next->address()) it = it ->next;
    if (it->next == nullptr) return false;
    else {
        tem = it->next;
        it->next = tem->next;
        tem->next = nullptr;
        delete tem;
        return true;
    }
}

std::string Group::EmailNode::address() const {
    return email;
}

Group::EmailNode * Group::EmailNode::findAddress( const std::string &s ) {
    EmailNode *it = this;
    while(it) {
        if (s == it->email) return it;
        it = it->next;
    }
    return nullptr;
}

Group::GroupNode::GroupNode( Group *g ) {
    gp = g;
    next = nullptr;
}

Group::GroupNode::~GroupNode() {/*
                                 GroupNode *tem = this;
                                 GroupNode *temtem;
                                 while(tem->next) {
                                 temtem = tem;
                                 tem = tem->next;
                                 delete temtem->gp;
                                 delete temtem;
                                 }
                                 delete tem->gp;
                                 delete tem;*/
    if (this->gp) delete this->gp;
    if (this->next) delete this->next;
}

Group * Group::GroupNode::group() const {
    return gp;
}

void Group::GroupNode::addGroup(GroupNode *g) {
    GroupNode *tem = new GroupNode(g->group());
    GroupNode *it = this;
    while (it->next && g->group()->gn > it->next->group()->gn)
        it = it->next;
    if (it->next == nullptr) it->next = tem;
    else {
        tem->next = it->next;
        it->next = tem;
    }
}

bool Group::GroupNode::removeGroup( GroupNode*g ) {
    GroupNode *tem = this;
    GroupNode *it = this;
    while (it->next && g->group()->gn != it->next->gp->gn) it = it ->next;
    if (it->next == nullptr) return false;
    else {
        tem = it->next;
        it->next = tem->next;
        delete tem;
        return true;
    }
}

bool Group::GroupNode::removeAddress( const std::string &s ) {
    GroupNode *it = this;
    while(it && it->group()->removeAddress(s) == false) it = it->next;
    if (it) return true;
    return false;
}

bool Group::GroupNode::removeGroup (const std::string &s) {
    GroupNode *it = this;
    if (it->group()->removeGroup(s)) return true;
    while(it) {
        if (!it->next) break;
        if (s == it->next->group()->name()) {
            GroupNode *tem = it->next;
            it->next = tem->next;
            tem->next = nullptr;
            delete tem;
            return true;
        }
        if(it->next->group()->removeGroup(s)) return true;
        it = it->next;
    }
    return false;
}

Group::GroupNode * Group::GroupNode::findGroup( const std::string &s ) {
    GroupNode *it = this;
    while(it) {
        if (it->group()->findGroup(s)) return it;
        it = it->next;
    }
    return nullptr;
}

Group::GroupNode * Group::GroupNode::findAddress( const std::string &s ) {
    GroupNode *it = this;
    while(it) {
        if (it->group()->findAddress(s)) return it;
        it = it->next;
    }
    return nullptr;
}

Group::GroupNode * Group::findGroup( const std::string &s ) {
    if (s == gn) {
        return gNode;//lol
    } else {
        GroupNode *it = gNode;
        while(it) {
            if (s == it->group()->gn) return it;
            it = it->next;
        }
        it = gNode;
        while(it) {
            if(it->findGroup(s)) return it->findGroup(s);
            it = it->next;
        }
        return nullptr;
    }
}

Group::EmailNode * Group::findAddress( const std::string &s ) {
    if (eNode->findAddress(s)) return eNode->findAddress(s);
    GroupNode *it = gNode;
    while(it) {
        if (it->group()->findAddress(s)) return it->group()->findAddress(s);
        it = it->next;
    }
    return nullptr;
}

std::ostream & operator<<(std::ostream &out, Group::GroupNode *g ) {
    Group::GroupNode *it = g;
    while(it) {
        out << "\t" << it->group()->name() << std::endl;
        if (it->group()->eNode) {
            out << "\t" << "[" << it->group()->eNode->address();
            Group::EmailNode *it2 = it->group()->eNode->next;
            while(it2) {
                out << ", " << it2->address();
                it2 = it2->next;
            }
            out << "]" << std::endl;
        }
        if (it->group()->gNode)
            out << "\t" << it->group()->gNode;
        it = it->next;
    }
    return out;
}

std::ostream & operator<<( std::ostream &out, Group &g ) {
    out << g.name();
    out << std::endl;
    if (g.eNode) {
        out << "[" << g.eNode->address();
        Group::EmailNode *it2 = g.eNode->next;
        while(it2) {
            out << ", " << it2->address();
            it2 = it2->next;
        }
        out << "]" << std::endl;
    }
    if (g.gNode) out << g.gNode << std::endl;
    return out;
}

std::ostream & operator<<(std::ostream &out, Group::EmailNode &g ) {
    out << g.address();
    return out;
}

std::ostream & operator<<(std::ostream &out, Group::GroupNode &g ) {
    out << "[" << g.gp->name() << "]" ;
    return out;
}
