#include"Bingo_Header.h"

void* confirm_t(void* arg)
{
    conf_p p=*(conf_p*)arg;
    data d;
    int val;
    while((val = recv(((player*)(p.p->d))->sd,&d,sizeof(data),0))==sizeof(data));
    pthread_mutex_lock(&p.pl->lock);
    close(((player*)p.p->d)->sd);
    p.p->n->p=p.p->p;
    p.p->p->n=p.p->n;
    free(p.p->d);
    free(p.p);
    --p.pl->n;
    server_started_screen(p.w,p.pan,((player*)p.pl->l.h->d)->ad,p.pl->n);
    pthread_mutex_unlock(&p.pl->lock);
}
