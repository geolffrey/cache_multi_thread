/*
 * This is the source code of SpecNet project
 * It is licensed under MIT License.
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#include "testoncachemlru.h"
#include "spec/specstatic.h"
#include <memory>

TestOnCacheMLRU::TestOnCacheMLRU()
{

}


TestOnCacheMLRU::~TestOnCacheMLRU() {
  onStop();
}

void  TestOnCacheMLRU::onStart(std::shared_ptr<IConfig>  &cfg)  {
  int64_t  capacity  = cfg.get()->getLongValue("capacity");
  assert(capacity > 0);
  onStop() ;
  cache  =  new OnCacheMLRU<TKey *, Elem *>(capacity);
  return;
}

void  TestOnCacheMLRU::onStop()  {
  if (cache) {
    delete  cache;
    cache  =  nullptr;
  }
  return;
}

void  TestOnCacheMLRU::insert(void  *elem)  {
  Elem  *e  =  static_cast<Elem *>(elem);
  cache->insertNode(&(e->key),
                    std::make_shared<Elem *>(e));
  return;
}

bool  TestOnCacheMLRU::exist(void  *elem)  {
  bool  re  =  false;
  Elem  *e  =  static_cast<Elem *>(elem);
  std::shared_ptr<Elem *> p_elem  =  cache->getData(&e->key);
  if (p_elem  &&  *p_elem.get() == e) {
     re  =  true;
  }
  return  re;
}

const char *  TestOnCacheMLRU::get_algorithm_name()  {
  static ConstString my_name("OnCacheMLRU");
  return  my_name.c_str;
}

