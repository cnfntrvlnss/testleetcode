/*************************************************************************
	> File Name: testLFUCache.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 18 Dec 2016 07:52:27 AM EST
 ************************************************************************/

#include "stdafx.h"

#include <cassert>
#include <list>
#include <map>
#include<iostream>
using namespace std;

class LFUCache{
    struct EntityBox;
    struct Entity{
        int key;
        int value;
        Entity* next;
        Entity* prev;
        EntityBox* box;
    };
    struct EntityBox{
        int count;
        Entity *near;
        Entity *far;
        EntityBox *next;
        EntityBox *prev;
    };
    map<int, Entity*> mKIdc;
    EntityBox *st;
    int cap;
public:
    LFUCache(int cap){
        this->cap = cap;
        this->st = NULL;
    };
    void validData(){
        int cnt = 0;
        int rcnt = 0;
        EntityBox *ptr = st;
        EntityBox *rptr = st;
        while(ptr != NULL){
            Entity *eptr = ptr->near;
            while(eptr){
                assert(eptr->box == ptr);
                cnt ++;
                eptr = eptr->next;
            }
            eptr = ptr->far;
            while(eptr){
                rcnt ++;
                eptr = eptr->prev;
            }
            if(ptr->prev){
                assert(ptr->prev->count < ptr->count);
            }
            if(ptr->next){
                assert(ptr->next->count > ptr->count);
                rptr = ptr->next;
            }
            ptr = ptr->next;
        }
        assert(rcnt == cnt);
        assert(cnt == mKIdc.size());
        cnt = 0;
        while(rptr != NULL){
            Entity *eptr = rptr->near;
            while(eptr){
                cnt ++;
                eptr = eptr->next;
            }
            rptr = rptr->prev;
        }
        assert(cnt == mKIdc.size());
    }
    int get(int key){
        validData();
        map<int, Entity*>::iterator it= mKIdc.find(key);
        if(it == mKIdc.end()) return -1;
        Entity *tmp = it->second;
        EntityBox *nbox = tmp->box;

        int ret = tmp->value;
        EntityBox *tmpbox = NULL;
        if(nbox->far == nbox->near){
            tmpbox = nbox;
            //nbox->count ++;
        }
        else{
            if(tmp->next == NULL){
                nbox->far = tmp->prev;
            }
            else{
                tmp->next->prev = tmp->prev;
            }
            if(tmp->prev == NULL){
                nbox->near = tmp->next;
            }
            else{
                tmp->prev->next = tmp->next;
            }
        }
        if(nbox->next == NULL){
            if(tmpbox == NULL){
                 tmpbox = new EntityBox;
                tmpbox->prev = nbox;
                tmpbox->next = NULL;
                tmpbox->count = nbox->count + 1;
                nbox->next = tmpbox;
                tmpbox->near = tmpbox->far = tmp;
                tmp->box = tmpbox;
                tmp->prev = tmp->next = NULL;
            }
            else{
                tmpbox->count ++;
                
            }
            tmpbox = NULL;
        }
        else if(nbox->next->count == nbox->count + 1){
            nbox->next->near->prev = tmp;
            tmp->next = nbox->next->near;
            tmp->prev = NULL;
            tmp->box = nbox->next;
            nbox->next->near = tmp;
            if(tmpbox != NULL){
                nbox->next->prev = nbox->prev;
                if(nbox->prev == NULL){
                    this->st = nbox->next;
                }
                else{
                    nbox->prev->next = nbox->next;
                }
                delete tmpbox;
            }
        }
        else{
            if(tmpbox != NULL){
                tmpbox->count ++;
            }
            else{
                tmpbox = new EntityBox;
                tmpbox->prev=nbox;
                tmpbox->next = nbox->next;
                tmpbox->count = nbox->count + 1;
                nbox->next = tmpbox;
                tmpbox->near = tmpbox->far = tmp;
                tmp->box = tmpbox;
                tmp->prev = tmp->next = NULL;
            }
            tmpbox = NULL;
        }

        validData();
        return ret;
    };
    void put(int key, int value){
        validData();
        Entity *tmp;
        EntityBox *nbox;
        if(mKIdc.find(key) == mKIdc.end()){
            if(mKIdc.size() == cap){
                Entity * rm = st->far;   
                if(rm->prev){
                    rm->prev->next = NULL;
                    st->far = rm->prev;
                }
                else{
                    st->far = NULL;
                    st->near = NULL;
                    EntityBox *rmb = st;
                    st = st->next;   
                    delete rmb;
                }
                mKIdc.erase(rm->key);
                delete rm;
            }
            tmp = new Entity;
            tmp->key = key;
            tmp->value = value;
            if(st == NULL){
                st = new EntityBox;
                st->count = 1;
                st->next = NULL;
                st->prev = NULL;
                st->far = NULL;
                st->near = NULL;
                nbox = st;
            }
            else if(st->count == 1){
                nbox = st;
            }
            else{
                nbox = new EntityBox;
                nbox->count = 1;
                nbox->next = st;
                nbox->prev = NULL;
                nbox->far = NULL;
                nbox->near = NULL;
                st->prev = nbox;
                st = nbox;
            }
        }
        else{
            tmp = mKIdc.find(key)->second;
            tmp->value = value;
            int count = tmp->box->count + 1;
            mKIdc.erase(key);
            EntityBox *myBox = tmp->box;
            nbox = myBox;

            if(tmp->prev){
                tmp->prev->next = tmp->next;
            }
            else{
                myBox->near = tmp->next;
            }
            if(tmp->next){
                tmp->next->prev = tmp->prev;
            }
            else{
                myBox->far = tmp->prev;
            }
            if(myBox->next){
                if(myBox->next->count == count) nbox = myBox->next;
                else{
                    nbox = new EntityBox;
                    nbox->count = count;
                    nbox->far = NULL;
                    nbox->near = NULL;
                    nbox->next = myBox->next;
                    myBox->next->prev = nbox;
                    nbox->prev = myBox;
                    myBox->next = nbox;
                }
            }
            else{
                nbox = new EntityBox;
                nbox->count = count;
                nbox->far = NULL;
                nbox->near = NULL;
                nbox->next = NULL;
                nbox->prev = myBox;
                myBox->next = nbox;
            }
            if(myBox->near == NULL){
                assert(myBox->far == NULL);
                if(myBox->prev){
                    myBox->prev->next = myBox->next;
                }
                else{
                    st = myBox->next;
                }
                if(myBox->next){
                    myBox->next->prev = myBox->prev;
                }
                delete myBox;
            }
        }
        mKIdc[key] = tmp;
        tmp->box = nbox;
        if(nbox->near){
            tmp->prev= NULL;
            tmp->next = nbox->near;
            nbox->near->prev = tmp;
            nbox->near = tmp;
        }
        else{
            nbox->near = nbox->far = tmp;
            tmp->prev = NULL;
            tmp->next = NULL;
        }
        validData();
    };
};

TEST(DISABLED_LFUCache, first)
{
    LFUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1) == 1);
    cache.put(3, 3);
    assert(cache.get(2) == -1);
    assert(cache.get(3) == 3);
    cache.put(4, 4);
    assert(cache.get(1) == -1);
    assert(cache.get(3) == 3);
    assert(cache.get(4) == 4);
}
