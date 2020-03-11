#include"Bingo_Header.h"

void* confirm_t(void* arg)
{
	conf_p p=*(conf_p*)arg;
	data d;
	while(recv(((player*)(p.pl->d))->sd,&d,sizeof(data),0)!=0);
	pthread_mutex_lock(p.lock);
	p.pl->n->p=p.pl->p;
	p.pl->p->n=p.pl->n;
	free(p.pl->d);
	free(p.pl);
	server_started_screen(p.w,p.start,p.cancel,p.pan,((player*)p.pl->d)->ad,*p.n);
	pthread_mutex_unlock(p.lock);
}
