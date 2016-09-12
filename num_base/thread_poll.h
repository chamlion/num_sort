#include <functional>
#include "blocking_task_queue.h"
#include "functions.h"
#include <thread>
namespace num
{
  class thread_poll: num::noncopyable
 {
   public :
   typedef std::function<void ()> Task;
   explicit thread_poll (int thread_num);
   ~thread_poll();
  void start();
  void stop();
  void run(const Task& f);
   private:
  void run_in_thread();
  void quit();
 int thread_num_;
  std:: mutex mutex_;
  std::vector<std::thread *> threads;
  num::blocking_task_queue<Task> queue_;
  bool running;
  
 };
}
