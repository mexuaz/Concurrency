#ifndef FORK_H
#define FORK_H

#include <cstddef> // size_t
#include <mutex>
#include <condition_variable>

class fork
{
    size_t m_id;
    bool m_available = true;
    std::mutex m_mt; // this object has no longer have copy constructor since mutex doesn't have
    std::condition_variable m_cv;
public:
    fork(size_t id);
    size_t id( void ) const;
    void pick_up( void );
    void put_down( void );
};



#endif // FORK_H
