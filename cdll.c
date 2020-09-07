#include"cdll.h"
void init(cdll *l,int size,int(*cmp)(void*,void*),void(*disp)(void*),void(*cpy)(void* Destinaion,void* Source))
{
    l->size=size;
    l->cmp=cmp;
    l->disp=disp;
    l->cpy=cpy;
    l->h=NULL;
}
void display(cdll l,char* y)
{
    if(l.h==NULL)
	return;
    node *temp=l.h;
    do{
	(l.disp)(temp->d);
	printf("%s",y);
	temp=temp->n;
    }while(temp!=l.h);
}

node* createnode(void *d,void (*cpy)(void*,void*),int size)
{
    node *n=malloc(sizeof(node));
    if(n==NULL||d==NULL)
	return NULL;
    n->d=malloc(size);
    cpy(n->d,d);
    n->p=n->n=n;
    return n;
}

int insertl(cdll* l,void *d,int pos)
{
    node *t=createnode(d,l->cpy,l->size),*temp;
    int i=1;
    if(t==NULL)
	return 0;
    if(l->h==NULL)
    {
	t->n=t->p=t;
	l->h=t;
	return 1;
    }
    temp=l->h;
    if(pos<0)
    {
	pos=-pos;
	do
	{
	    temp=temp->p;
	    ++i;
	}while(i<pos&&temp!=l->h);
	t->n=temp;
	t->p=temp->p;
	temp->p->n=t;
	temp->p=t;
	if(temp==l->h)
	    l->h=t;
	return 1;
    }
    if(pos==0)
    {
	t->n=l->h;
	t->p=l->h->p;
	l->h->p->n=t;
	l->h->p=t;
	l->h=t;
	return 1;
    }
    while(i<pos&&temp->n!=l->h)
    {
	temp=temp->n;
	++i;
    }
    t->p=temp;
    t->n=temp->n;
    temp->n->p=t;
    temp->n=t;
    return 1;
}

void delnode(cdll *l,int pos)
{
    node *t=l->h;
    int i=0;
    if(t==NULL)
	return;

    do 
    {
	if(i==pos)
	{
	    t->p->n=t->n;
	    t->n->p=t->p;
	    if(t==l->h)
		l->h=t->n;
	    free(t->d);
	    free(t);
	    return;
	}
	++i;
	t=t->n;
    }while(t!=l->h);
}

void freecdll(cdll list)
{
    node *t1=list.h,*t2;
    if(list.h==NULL)
	return;
    do
    {
	t2=t1;
	t1=t1->n;
	free(t2->d);
	free(t2);
    }while(t1!=list.h);
}

void* pop(cdll *l)
{
    node* t=l->h;
    void *data;
    if(l->h==NULL)
	return NULL;
    data=l->h->d;
    t->n->p=t->p;
    t->p->n=t->n;
    t=t->n;
    free(l->h);
    if(t==l->h)
	l->h=NULL;
    else
	l->h=t;
    return data;
}

void* topvalue(cdll l)
{
    if(l.h==NULL)
	return NULL;
    void* data=malloc(l.size);
    if(data==NULL)
	return NULL;
    l.cpy(data,l.h->d);
    return data;
}

void * deq(cdll *l)
{
    void *data;
    if(l->h==NULL)
	return NULL;
    node *t=l->h->p;
    if(t==l->h)
    {
	data=l->h->d;
	free(l->h);
	l->h=NULL;
	return data;
    }
    data=t->d;
    t->p->n=t->n;
    t->n->p=t->p;
    free(t);
    return data;
}

void* frontvalue(cdll l)
{
    if(l.h==NULL)
	return NULL;
    void* data=malloc(l.size);
    if(data==NULL)
	return NULL;
    l.cpy(data,l.h->p->d);
    return data;
}

int insorder(cdll *l,void* data,char order)
{
    if(order!='d'&&order!='D'&&order!='a'&&order!='A')
	return -1;
    node *t=l->h,*temp=createnode(data,l->cpy,l->size);
    if(temp==NULL)
	return -2;
    if(t==NULL)
    {
	l->h=temp;
	return 1;
    }
    if(order=='a'||order=='A')
    {
	do
	{
	    if(l->cmp(t->d,data)>0)
	    {
		temp->n=t;
		temp->p=t->p;
		t->p->n=temp;
		t->p=temp;
		if(t==l->h)
		    l->h=temp;
		return 1;
	    }
	    t=t->n;
	}while(t!=l->h);
	temp->n=t;
	temp->p=t->p;
	t->p->n=temp;
	t->p=temp;
	return 1;
    }
    do
    {
	if(l->cmp(t->d,data)<0)
	{
	    temp->n=t;
	    temp->p=t->p;
	    t->p->n=temp;
	    t->p=temp;
	    if(t==l->h)
		l->h=temp;
	    return 1;
	}
	t=t->n;
    }while(t!=l->h);
    temp->n=t;
    temp->p=t->p;
    t->p->n=temp;
    t->p=temp;
    return 1;
}

void rotatecdll(cdll* l,int x)
{
    if(l->h==NULL||l->h->n==l->h||x==0)
	return;
    for(;x>0;--x)
	l->h=l->h->p;
    for(;x<0;++x)
	l->h=l->h->n;
}

void* center(cdll l)
{
    node *t1=l.h,*t2=l.h;
}
