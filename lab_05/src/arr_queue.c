#include"../inc/arr_queue.h"



void init_arr_queue(arr_t *queue)
{
    queue->begin = -1;
    queue->end = -1;
    queue->size = 0;
}


int owerflow_arr_queue(arr_t queue)
{
    return (queue.size == 1000) ? 1 : 0;
    //((queue.begin == queue.end + 1) || (queue.begin == 0 && queue.end == MAX_ELEMS - 1));
}



int clear_check_arr_queue(arr_t queue)
{
    return queue.begin == -1 ? 1 : 0;
}


void push_arr_queue(arr_t *queue, int elem)
{
    // if (owerflow_arr_queue(*queue))
    // {
    //     printf("\n\nОшибка: очередь переполнена\n\n");
    //     return;
    // }
    
    if (queue->begin == -1)
    {
        queue->begin = 0;
    }

    queue->end = (queue->end + 1) % MAX_ELEMS;
    queue->arr[queue->end] = elem;
    queue->size++;
}


void pop_arr_queue(arr_t *queue)
{
    // if (clear_check_arr_queue(*queue))
    // {
    //     printf("\n\nОчередь пустая\n\n");
    //     return;
    // }

    if (queue->begin == queue->end)
    {
        queue->begin = -1;
        queue->end = -1;
    }
    else
    {
        queue->begin = (queue->begin + 1) % MAX_ELEMS;
        queue->size--;
    }
}


void print_arr_queue(arr_t queue)
{
    if (clear_check_arr_queue(queue))
    {
        printf("\n\nОчередь пустая\n\n");
        return;
    }

    puts("\n");

    for (int i = queue.begin; i <= queue.end; i++)
    {
        printf("%d ", queue.arr[i]);
    }

    puts("\n");
}


float min_of_three(float a, float b, float c)
{
    float min = a;

    if (min > b)
    {
        min = b;
    }

    if (min > c)
    {
        min = c;
    }

    return min;
}




void task_arr(void)
{
    arr_t queue1;
    init_arr_queue(&queue1);

    int q1_req_in = 0;  // заявок вошло
    int q1_req_out = 0; // заявок вышло
    int q1_req_all = 0; // количество раз работы с очередью
    int q1_len_all = 0; // вся длина очереди (для среднего значения)
    float q1_time_all = 0; // общее время для всей первой очереди
    int q1_len_cur = 0; // текущая длина очереди

    arr_t queue2;
    init_arr_queue(&queue2);

    int q2_req_in = 0; 
    int q2_req_out = 0;
    int q2_req_all = 0;
    int q2_len_all = 0;
    float q2_time_all = 0; // общее время для всей второй очереди
    int q2_len_cur = 0;
    int q2_back_in_end = 0;

    // дополнительные переменные подсчета

    float q1_cur_time_in = 0;
    //float q1_cur_time_work = 0;
    float q2_cur_time_in = 0;
    //float q2_cur_time_work = 0;

    //int q1_req_out_all = 0;

    int queue_type = 0;
    float oa_time = 0;


    float time_all = 0; // общее время

    int to_show = 0;

    int in_push = 0, in_pop = 0;

    while (q1_req_out < 1000)
    {
        if (q1_cur_time_in == 0)
        {
            q1_cur_time_in = rand_time(T1_IN_B, T1_IN_E);
        }

        if (q2_cur_time_in == 0)
        {
            q2_cur_time_in = rand_time(T2_IN_B, T2_IN_E);
        }

        if (oa_time == 0)
        {
            // если время работы аппарата = 0, то загрузить его работой с первой очередью, иначе - со второй
            if (!clear_check_arr_queue(queue1))
            {
                //puts("YESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS!!!!!!!");
                oa_time = rand_time(T1_OUT_B, T1_OUT_E);
                queue_type = 1;
                pop_arr_queue(&queue1);

                in_pop++;

                q1_len_cur--;
                q1_req_all++;
                q1_len_all += q1_len_cur;

                q1_time_all += oa_time;
            }
            else if (!clear_check_arr_queue(queue2))
            {
                // puts("!!!!!!!YESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
                oa_time = rand_time(T2_OUT_B, T2_OUT_E);
                queue_type = 2;
                pop_arr_queue(&queue2);

                q2_len_cur--;
                q2_req_all++;
                q2_len_all += q2_len_cur;

                q2_time_all += oa_time;
            }            
        }
        // если аппарат в работе, но с заявкой второго типа и появилась заявка первого типа, то нужно удалить из работы вторую заявку и подать первую
        else if ((queue_type == 2) && (!clear_check_arr_queue(queue2)))
        {
            push_arr_queue(&queue2, 2);
            q2_time_all -= oa_time;
            oa_time = 0;
            //q2_req_in++;
            q2_back_in_end++;

            q2_len_cur++;
            q2_req_all++;
            q2_len_all += q2_len_cur;
            continue;
        }

        float min_time = 0;

        //printf("\n\n oa = %f\nq1_cur_time_in = %f\nq2_cur_time_in = %f\n\n", oa_time, q1_cur_time_in, q2_cur_time_in);

        // если обработки нет, то ищем тот элемент, что будет добавлен быстрее (в 1 или во 2 очередь)
        if (oa_time == 0)
        {
            min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, q1_cur_time_in);
        }
        // если есть обработки, то решаем, какой процесс быстрее - произвести обработку или добавить элемент из какой-то из очередей
        else
        {
            min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, oa_time);
        }

        //printf("\nmin time = %f\n\n", min_time);

        // если обработка быстрее
        if (oa_time == min_time)
        {
            //printf("\n\ntype = %d\n\n", queue_type);
            oa_time = 0;

            if (queue_type == 1)
            {
                //puts("yessssssssssssssssssssssssssssssssssssssssss");
                q1_req_out++;
            }
            else if (queue_type == 2)
            {
                q2_req_out++;
            }
        }

        //printf("\n\n oa = %f\nq1_cur_time_in = %f\nq2_cur_time_in = %f\n\n", oa_time, q1_cur_time_in, q2_cur_time_in);

        // если добавлене элемента в 1ую очередь быстрее
        if (q1_cur_time_in == min_time)
        {
            //puts("YESSSSSSSSSSSSSSSSSSSSSSSSSSS");
            push_arr_queue(&queue1, 1);

            in_push++;

            q1_req_in++;
            q1_len_cur++;
            q1_req_all++;
            q1_len_all += q1_len_cur;
        }
        // если добавлене элемента в 2ую очередь быстрее
        if (q2_cur_time_in == min_time)
        {
            push_arr_queue(&queue2, 2);

            q2_req_in++;
            q2_len_cur++;
            q2_req_all++;
            q2_len_all += q2_len_cur;
        }


        // Оставшееся время для добавления заявки
        q1_cur_time_in -= min_time;
        q2_cur_time_in -= min_time;

        if (oa_time >= min_time)
        {
            oa_time -= min_time;
        }

        time_all += min_time;


        // info every 100
        if ((q1_req_out % 100 == 0) && (q1_req_out != to_show))
        {
            to_show = q1_req_out;
            printf("Заявок 1го типа обработано = %d\n\n", q1_req_out);

            printf("Текущая длина очереди 1го типа = %d\n", q1_len_cur);
            printf("Средняя длина очереди 1го типа = %f\n\n", (float)(q1_len_all / q1_req_all));

            printf("Текущая длина очереди 2го типа = %d\n", q2_len_cur);
            printf("Средняя длина очереди 2го типа = %f\n\n\n", (float)(q2_len_all / q2_req_all));
        }

    }

    float avg_q1_in = (T1_IN_B + T1_IN_E) / 2;
    float all_avg_q1_in = avg_q1_in * COUNT;

    float avg_q1_out = (T1_OUT_B + T1_OUT_E) / 2;
    float all_avg_q1_out = avg_q1_out * COUNT;

    float avg_q2_in = (float)(T2_IN_B + T2_IN_E) / (float)2;

    
    float estimate_model_time;

    if (all_avg_q1_in > all_avg_q1_out)
    {
        estimate_model_time = all_avg_q1_in;
    }
    else
    {
        estimate_model_time = all_avg_q1_out;
    }

    float percent_oa = fabs((time_all - estimate_model_time) * 100 / estimate_model_time);

    printf("\n\nОбщее время моделировния = %f \
    \nПогрешность моделирования = %f процентов\n\n", time_all, percent_oa);

    printf("\nЗаявок вошло в 1ую очередь = %d \
    \nЗаявок 1ой очереди вышло = %d \
    \nСреднее время обработки заявки в 1ой очереди (ожидаемое) = %f\n\n", q1_req_in, q1_req_out, avg_q1_in);

    printf("\nЗаявок вошло во 2ую очередь = %d \
    \nЗаявок 2ой очереди вышло = %d \
    \nСреднее время обработки заявки в 2ой очереди (ожидаемое) = %f\
    \nЗаявок 2го типа вернулось обратно в конец очереди = %d\n\n", q2_req_in, q2_req_out, avg_q2_in, q2_back_in_end);

    float time_in1 = time_all / avg_q1_in;
    float percent_time_in1 = fabs((q1_req_in - time_in1) * 100 / time_in1);

    float time_in2 = time_all / avg_q2_in;
    float percent_time_in2 = fabs((q2_req_in - time_in2) * 100 / time_in2);

    printf("Погрешность ввода заявок в 1ую очередь %f процентов \
    \nПогрешность ввода заявок во 2ую очередь %f процентов\n\n", percent_time_in1, percent_time_in2);


    float all_estimate_work = q1_time_all + q2_time_all;
    float time_wait = time_all - all_estimate_work;

    printf("\nВремя простоя = %f\n\n", fabs(time_wait));
}