/*
 * Network stack in userspace (NUSE) for POSIX userspace backend
 * Copyright (c) 2015 Hajime Tazaki
 *
 * Author: Hajime Tazaki <tazaki@sfc.wide.ad.jp>
 */

#ifndef NUSE_H
#define NUSE_H

struct pollfd;
struct SimDevice;
struct SimSocket;

/* nuse.c */
struct nuse_socket {
	struct SimSocket *kern_sock;
	int refcnt;
	int flags;
};

struct nuse_fd {
	int real_fd;
	struct epoll_fd *epoll_fd;
	struct nuse_socket *nuse_sock;
};
extern struct nuse_fd nuse_fd_table[1024];
void nuse_dev_rx(struct SimDevice *dev, char *buf, int size);

/* nuse-fiber.c */
void *nuse_fiber_new(void * (*callback)(void *),
		     void *context, uint32_t stackSize, const char *name);
void nuse_fiber_start(void *handler);
int nuse_fiber_isself(void *handler);
void nuse_fiber_wait(void *handler);
int nuse_fiber_wakeup(void *handler);
void nuse_fiber_free(void *handler);
void *nuse_fiber_new_from_caller(uint32_t stackSize, const char *name);
int nuse_fiber_is_stopped(void *handler);
void nuse_fiber_stop(void *handler);
void nuse_add_timer(unsigned long ns, void *(*func) (void *arg),
		    void *arg, void *handler);
void nuse_task_add(void *fiber);
void nuse_set_affinity(void);

/* nuse-poll.c */
int nuse_poll(struct pollfd *fds, unsigned int nfds,
	struct timespec *end_time);

/* nuse-syscalls.c */
void nuse_syscall_proxy_init(void);
void nuse_syscall_proxy_exit(void);

#endif /* NUSE_H */
