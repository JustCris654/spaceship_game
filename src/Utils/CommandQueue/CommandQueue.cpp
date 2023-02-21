#include "CommandQueue.hpp"

CommandQueue::CommandQueue() : m_Queue() {}

void CommandQueue::push(const Command &command) {
    m_Queue.push(command);
}

Command CommandQueue::pop() {
    Command command = m_Queue.back();
    m_Queue.pop();
    return command;
}

bool CommandQueue::isEmpty() {
    return m_Queue.empty();
}