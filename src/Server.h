#pragma once

class Server {
public:
  void MoveObject(Object* myObj, Object* target);
  void MoveObject(Object* myObj, uint32_t x, uint32_t y);
};


