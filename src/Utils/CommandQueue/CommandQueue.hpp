#include <queue>

#include "../Command.hpp"

class CommandQueue {
  public:
    CommandQueue();
    void    push(const Command &);
    Command pop();
    bool    isEmpty();

  private:
    std::queue<Command> m_Queue;
};