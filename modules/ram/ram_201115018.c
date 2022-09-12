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

//#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Practica 2, Laboratorio SO 1");
MODULE_AUTHOR("Joel Estuardo Rodriguez Santos");

//Funcion que se ejecutara cada vez que se lea el archivo con el comando CAT
static int write(struct seq_file *file, void *v)
{   
    struct sysinfo si;

    //Definir función para conseguir los kb de la ram
    #define K(x) ((x)<< (PAGE_SHIFT-10))

    si_meminfo(&si);
    seq_printf(file, "{\n");
    seq_printf(file, "\"total\": %8lu, \n",K(si.totalram));
    seq_printf(file, "\"free\": %lu, \n",K(si.freeram));
    seq_printf(file, "\"used\": %lu \n",K(si.totalram)-K(si.freeram));
    seq_printf(file, "}\n");

    #undef K
    return 0;
}
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
    proc_create("ram_201115018", 0, NULL, &operaciones);
    printk(KERN_INFO "201115018\n");
    return 0;
}

//Funcion a ejecuta al remover el modulo del kernel con rmmod
static void _remove(void)
{
    remove_proc_entry("ram_201115018", NULL);
    printk(KERN_INFO "Sistemas Operativos 1\n");
}

module_init(_insert);
module_exit(_remove);

//Obtener información de la ram
