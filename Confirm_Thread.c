#include"Bingo_Header.h"

void* confirm_t(void* arg)
{
	conf_p p=*(conf_p*)arg;
	data d;
	while(recv(((player*)(p.p->d))->sd,&d,sizeof(data),0)!=0);
	pthread_mutex_lock(p.lock);
	close(((player*)p.p->d)->sd);
	p.p->n->p=p.p->p;
	p.p->p->n=p.p->n;
	free(p.p->d);
	free(p.p);
	--(*(p.n));
	server_started_screen(p.w,p.pan,((player*)p.p->d)->ad,*(p.n));
	pthread_mutex_unlock(p.lock);
}
