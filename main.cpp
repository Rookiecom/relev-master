#include"basic_level.h"
#include <string>
#include<time.h>
/* 
0->HINI
1->HDEL
2->HEXITS
3->HGET
4->HGETALL
5->HINCRBY X
5->HKEYS 
6->HLEN
7->HMGET
8->HMSET
9->HSET
10->HSETNX
11->HVALS
12->HTEST
*/

char* order_table[13]={"HINIT","HDEL","HEXITS","HGET","HGETALL",
"HKEYS","HLEN","HMGET","HMSET","HSET","HSETNX","HVALS","HTEST"};
int numoftable;
uint8_t t_key[KEY_LEN],t_value[VALUE_LEN];
uint8_t *pkey;
char name[10];
level_hash* t[10];
int main()
{
    
    printf("请输入命令\n");
    int op;
    while(1)
    {
        char order[10];
        scanf("%s",order);
        for(int i=0;i<13;i++) 
            if(!strcmp(order,order_table[i]))
            {
                op=i;
                break;
            } 
        switch (op)
        {
            case 0://0->HINI
            {
                memset(name,0,sizeof(name));
                uint64_t size;
                scanf("%s%lu",name,&size);
                t[numoftable++]=level_init(size,name);
                break;   
            }
            case 1://1->HDEL
            {
                memset(t_key,0,sizeof(t_key));
                memset(name,0,sizeof(name));
                scanf("%s%s",name,t_key);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name))  printf("(interger) %d\n",!level_delete(t[i],t_key));
                    break;
                }
                break; 
            }
            case 2://2->HEXITS
            {
                memset(name,0,sizeof(name));
                memset(t_key,0,sizeof(t_key));
                scanf("%s%s",name,t_key);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        if(level_dynamic_query(t[i],t_key))
                            printf("(interger) 1\n");
                        else printf("(interger) 0\n");
                    }
                    break;    
                }
                break; 
            }
            case 3://3->HGET
            {
                memset(name,0,sizeof(name));
                memset(t_key,0,sizeof(t_key));
                scanf("%s%s",name,t_key);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        pkey=level_dynamic_query(t[i],t_key);
                        if(pkey!=NULL) printf("%s\n",pkey );
                        else printf("(nil)\n");
                    }   
                    break;       
                }
                break; 
            }
            case 4://4->HGETALL
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        for(int j=0;j<t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[0][j].token[k])
                                    printf("%s %s\n",t[i]->buckets[0][j].slot[k].key,t[i]->buckets[0][j].slot[k].value);
                            }
                        }
                        for(int j=0;j<t[i]->total_capacity-t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[1][j].token[k])
                                    printf("%s %s\n",t[i]->buckets[1][j].slot[k].key,t[i]->buckets[1][j].slot[k].value);
                            }
                        }
                    }
                    break;
                }
                break; 
            }
            case 5://5->HKEYS 
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        for(int j=0;j<t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[0][j].token[k])
                                    printf("%s\n",t[i]->buckets[0][j].slot[k].key);
                            }
                        }
                        for(int j=0;j<t[i]->total_capacity-t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[1][j].token[k])
                                    printf("%s\n",t[i]->buckets[1][j].slot[k].key);
                            }
                        }
                    }
                    break;
                }
                break; 
            }
            case 6://6->HLEN
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        printf("(interger) %d\n",t[i]->level_item_num[0]+t[i]->level_item_num[1]);
                    }
                    break;
                }
                break;
            }
            case 7://7->HMGET
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        while(1)
                        {
                            char c=getchar();
                            int number = 0;
                            memset(t_key,0,sizeof(t_key));
                            while(c!=' ' && c!='\n')
                            {
                                t_key[number++]=c;
                                c=getchar();
                            }
                            if((c==' ' || c=='\n') && number ==0) continue;
                            else t_key[number]='\0';
                            pkey=level_dynamic_query(t[i],t_key);
                            if(pkey==NULL) printf("(nil)\n");
                            else printf("%s\n",pkey);
                            if(c=='\n') break;
                        }
                    }
                    break;
                }
                break; 
            }
            case 8://8->HMSET
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        char c;
                        while((c=getchar())==' ');
                        int number;
                        while(1)
                        {
                            number=0;
                            memset(t_key,0,sizeof(t_key));
                            memset(t_value,0,sizeof(t_value));
                            while(c!=' ' && c!='\n')
                            {
                                t_key[number++]=c;
                                c=getchar();
                            }
                            t_key[number]='\0';
                            number=0;
                            while((c=getchar())==' ');
                            while(c!=' ' && c!='\n')
                            {
                                t_value[number++]=c;
                                c=getchar();
                            }
                            if(c==' ') while((c=getchar())==' ');
                            t_value[number]='\0';
                            level_insert(t[i],t_key,t_value);
                            if(c=='\n') break;
                        }
                        printf("OK\n");
                    }
                    break;
                }
                break; 
            }
            case 9://9->HSET
            {
                memset(t_key,0,sizeof(t_key));
                memset(name,0,sizeof(name));
                memset(t_value,0,sizeof(t_value));
                uint8_t new_value[VALUE_LEN];
                scanf("%s%s%s",name,t_key,new_value);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        if(level_dynamic_query(t[i],t_key)==NULL) 
                        {
                            level_insert(t[i],t_key,new_value);
                            printf("(interger) 1\n");
                        }
                        else
                        {
                            level_update(t[i],t_key,new_value);
                            printf("(interger) 0\n");
                        }
                        
                    }
                    break;
                }
                break; 
            }
            case 10://10->HSETNX
            {
                memset(t_key,0,sizeof(t_key));
                memset(name,0,sizeof(name));
                memset(t_value,0,sizeof(t_value));
                uint8_t new_value[VALUE_LEN];
                scanf("%s%s%s",name,t_key,new_value);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        if(level_dynamic_query(t[i],t_key)==NULL) 
                        {
                            level_insert(t[i],t_key,new_value);
                            printf("(interger) 1\n");
                        }
                        else
                        {
                            printf("(interger) 0\n");
                        }
                        
                    }
                    break;
                }
                break; 
            }
            case 11://11->HVALS
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        for(int j=0;j<t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[0][j].token[k])
                                    printf("%s\n",t[i]->buckets[0][j].slot[k].value);
                            }
                        }
                        for(int j=0;j<t[i]->total_capacity-t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[1][j].token[k])
                                    printf("%s\n",t[i]->buckets[1][j].slot[k].value);
                            }
                        }
                    }
                    break;
                }
                break; 
            }
            case 12://HTEST
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                int level_size,insert_num;
               
                scanf("%d%d",&level_size,&insert_num);
                level_hash* level=level_init(level_size,name);
                uint64_t inserted = 0, i = 0;
                uint8_t key[KEY_LEN];
                uint8_t value[VALUE_LEN];
                clock_t start,end;
                for (i = 1; i < insert_num + 1; i ++)
                {
                    snprintf((char *)key, KEY_LEN, "%ld", i);
                    snprintf((char *)value, VALUE_LEN, "%ld", i);
                    if (!level_insert(level, key, value))                               
                    {
                        inserted ++;
                    }
                    else
                    {
                        printf("Expanding: space utilization & total entries: %f  %ld\n", \
                            (float)(level->level_item_num[0]+level->level_item_num[1])/(level->total_capacity*ASSOC_NUM), \
                            level->total_capacity*ASSOC_NUM);
                        level_expand(level);
                        level_insert(level, key, value);
                        inserted ++;
                    }
                }   
                printf("%ld items are inserted\n", inserted);
                start=clock();
                printf("The static search test begins ...\n");
                for (i = 1; i < insert_num + 1; i ++)
                {
                    snprintf((char *)key, KEY_LEN, "%ld", i);
                    uint8_t* get_value = level_static_query(level, key);
                    if(get_value == NULL)
                        printf("Search the key %s: ERROR! \n", key);
                }
                end=clock();
                printf("The static search test consumes %dms\n",1000 *(end-start)/CLOCKS_PER_SEC);
                start=clock();
                printf("The dynamic search test begins ...\n");
                for (i = 1; i < insert_num + 1; i ++)
                {
                    snprintf((char *)key, KEY_LEN, "%ld", i);
                    uint8_t* get_value = level_dynamic_query(level, key);
                    if(get_value == NULL)
                        printf("Search the key %s: ERROR! \n", key);
                }
                end=clock();
                printf("The dynamic search test consumes %dms\n",1000 * (end-start)/CLOCKS_PER_SEC);
                start=clock();
                printf("The update test begins ...\n");
                for (i = 1; i < insert_num + 1; i ++)
                {
                    snprintf((char *)key, KEY_LEN, "%ld", i);
                    snprintf((char *)value, VALUE_LEN, "%ld", i*2);
                    if(level_update(level, key, value))
                        printf("Update the value of the key %s: ERROR! \n", key);
                }
                end=clock();
                printf("The update search test consumes %dms\n",1000 * (end-start)/CLOCKS_PER_SEC);
                start=clock();
                printf("The deletion test begins ...\n");
                for (i = 1; i < insert_num + 1; i ++)
                {
                    snprintf((char *)key, KEY_LEN, "%ld", i);
                    if(level_delete(level, key))
                        printf("Delete the key %s: ERROR! \n", key);
                }
                end=clock();
                printf("The deletion search test consumes %dms\n",1000 * (end-start)/CLOCKS_PER_SEC);
                printf("The number of items stored in the level hash table: %ld\n", level->level_item_num[0]+level->level_item_num[1]);    
                level_destroy(level);
            }
        }
    }
    return 0;
}