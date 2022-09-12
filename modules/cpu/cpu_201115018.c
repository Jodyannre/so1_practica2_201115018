#include <linux/module.h>
// para usar KERN_INFO
#include <linux/kernel.h>

//Header para los macros module_init y module_exit
#include <linux/init.h>
//Header necesario porque se usara proc_fs
#include <linux/proc_fs.h>
/* for copy_from_user *
#include <asm/uaccess.h>	
/* Header para usar la lib seq_file y manejar el archivo en /proc*/
#include <linux/seq_file.h>
#include <linux/hugetlb.h>

/*Modulos para la cpu*/
#include <linux/sched.h>
#include <linux/sched/signal.h>

/*#include <unistd.h>*/
/*#include <sys/types.h>
#include <linux/pwd>
*/


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Practica 2, Laboratorio SO 1");
MODULE_AUTHOR("Joel Estuardo Rodriguez Santos");

struct task_struct *cpu;
struct task_struct *child;
struct list_head *lstProcess;

//Funcion que se ejecutara cada vez que se lea el archivo con el comando CAT
static int write(struct seq_file *file, void *v)
{   
    //Definir función para conseguir los kb de la ram
    long memoriaTotal;
    int contadorProcesos = 0;
    int contadorHijos = 0;
    /*
    #define TASK_RUNNING 0
    #define TASK_INTERRUPTIBLE 1
    #define TASK_UNINTERRUPTIBLE 2
    #define TASK_ZOMBIE 4
    #define TASK_STOPPED 8
    */
    seq_printf(file, "[\n");
    for_each_process(cpu){
        /*Obtener memoria total*/
        if(cpu->mm){
            memoriaTotal = get_mm_rss(cpu->mm);
        }

        seq_printf(file, "{\n");
        seq_printf(file, "\"memoria\": %lu, \n", memoriaTotal/1024);
        seq_printf(file, "\"pid\": %d, \n", cpu->pid);
        seq_printf(file, "\"nombre\": \"%s\", \n", cpu->comm);
        seq_printf(file, "\"usuario\": %d, \n",cpu->real_cred->uid);
        seq_printf(file, "\"hijos\": [\n");
        list_for_each(lstProcess, &(cpu->children)){
            child = list_entry(lstProcess, struct task_struct, sibling);
            seq_printf(file, "{\n");
            seq_printf(file, "\"pid\": %d, \n", child->pid);
            seq_printf(file, "\"nombre\": \"%s\" \n", child->comm);
            seq_printf(file, "},\n");
            contadorHijos++;
        }
        seq_printf(file, "{}\n");
        seq_printf(file, "]\n");
        seq_printf(file, "},\n");
        //contadorHijos = 0;
        contadorProcesos++;
    }
    seq_printf(file, "{\n");
    /*
    seq_printf(file, "\"procesos\": %d,\n",contadorProcesos);
    seq_printf(file, "\"hijos\": %d\n",contadorHijos);
    seq_printf(file, "\"running\": %d, \n", TASK_RUNNING);
    seq_printf(file, "\"interruptible\": %d, \n", TASK_INTERRUPTIBLE);
    //seq_printf(file, "\"zombie\": \"%d\", \n", TASK_ZOMBIE);
    seq_printf(file, "\"stopped\":%d \n", TASK_STOPPED);
    */
    seq_printf(file, "}\n");
    seq_printf(file, "]\n");
    return 0;
}

/*
static char* getUserName(uid_t uid){
    struct passwd *pws;
    pws = getpwuid(uid);
        return pws->pw_name
}
*/

//Funcion que se ejecutara cada vez que se lea el archivo con el comando CAT
static int openFile(struct inode *inode, struct file *file)
{
    return single_open(file, write, NULL);
}

//Si el kernel es 5.6 o mayor se usa la estructura proc_ops
static struct proc_ops operaciones =
{
    .proc_open = openFile,
    .proc_read = seq_read
};

//Funcion a ejecuta al insertar el modulo en el kernel con insmod
static int _insert(void)
{
    proc_create("cpu_201115018", 0, NULL, &operaciones);
    printk(KERN_INFO "Joel Estuardo Rodriguez Santos\n");
    return 0;
}

//Funcion a ejecuta al remover el modulo del kernel con rmmod
static void _remove(void)
{
    remove_proc_entry("cpu_201115018", NULL);
    printk(KERN_INFO "Segundo Semestre 2022\n");
}

module_init(_insert);
module_exit(_remove);

//Obtener información de la ram
