#include <lwk/task.h>

id_t get_cpu_id_from_task(struct task_struct* ts)
{
	return ts->cpu_id;
}
