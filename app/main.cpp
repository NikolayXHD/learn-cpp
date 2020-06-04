#include <iostream>
#include <map>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
 public:
  // Получить статистику по статусам задач конкретного разработчика
  [[nodiscard]] const TasksInfo &
  GetPersonTasksInfo(const string &person) const {
    const auto &it = infos_by_person_.find(person);
    if (it == infos_by_person_.cend()) {
      return empty_;
    }
    return it->second;
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string &person) {
    infos_by_person_[person][TaskStatus::NEW]++;
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string &person, int task_count) {
    const auto &it_infos = infos_by_person_.find(person);
    if (it_infos == infos_by_person_.cend()) {
      return tie(empty_, empty_);
    }
    auto& infos = it_infos->second;
    if (task_count == 0) {
      return tie(empty_, infos);
    }

    const auto infos_copy = infos;
    TasksInfo updated_infos;
    TasksInfo intact_infos;
    for (const auto& it_cp: infos_copy) {
      auto status = it_cp.first;
      if (status == TaskStatus::DONE) {
        break;
      }
      int updated = min(task_count, it_cp.second);
      int intact = it_cp.second - updated;
      if (updated > 0) {
        int& new_count = infos.find(status)->second;
        new_count -= updated;
        if (new_count == 0) {
          infos.erase(status);
        }
        auto next_status = static_cast<TaskStatus>((static_cast<int>(status) + 1));
        infos[next_status] += updated;
        updated_infos[next_status] = updated;
      }

      if (intact > 0) {
        intact_infos[status] = updated;
      }
    }

    return tie(updated_infos, intact_infos);
  }

 private:
  map<string, TasksInfo> infos_by_person_{};
  const TasksInfo empty_{};
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
       ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
       ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
       ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}