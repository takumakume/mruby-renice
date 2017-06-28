/*
** mrb_renice.c - Renice class
**
** Copyright (c) takumakume 2017
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"

#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

void priority_error_handler(mrb_state *mrb, int error)
{
  switch (error) {
    case EINVAL:
      mrb_raise(mrb, E_RUNTIME_ERROR, "which was not one of PRIO_PROCESS, PRIO_PGRP, or PRIO_USER");
    case ESRCH:
      mrb_raise(mrb, E_RUNTIME_ERROR, "No process was located using the which and who values specified");
    case EACCES:
      mrb_raise(mrb, E_RUNTIME_ERROR, "The caller attempted to set a lower nice value, but did not have the required privilege (on CAP_SYS_NICE)");
    case EPERM:
      mrb_raise(mrb, E_RUNTIME_ERROR, "A process was located, but its effective user ID did not match either the effective or the real user ID of the caller, and　was not privileged (on CAP_SYS_NICE)");
    default:
      mrb_raise(mrb, E_RUNTIME_ERROR, "unknown error");
  }
}

static mrb_value sys_getpriority(mrb_state *mrb, int which, int who)
{
  int prio;

  prio = getpriority(which, who);
  if (prio == -1) {
    priority_error_handler(mrb, errno);
  }

  return mrb_fixnum_value(prio);
}

static mrb_value sys_setpriority(mrb_state *mrb, int which, int who, int prio)
{
  int ret;

  ret = setpriority(which, who, prio);
  if (ret == -1) {
    priority_error_handler(mrb, errno);
    return mrb_false_value();
  }

  return mrb_true_value();
}

static mrb_value mrb_getpriority_process(mrb_state *mrb, mrb_value self)
{
  mrb_int pid;
  mrb_get_args(mrb, "i", &pid);
  return sys_getpriority(mrb, PRIO_PROCESS, pid);
}

static mrb_value mrb_setpriority_process(mrb_state *mrb, mrb_value self)
{
  mrb_int pid;
  mrb_int priority;
  mrb_get_args(mrb, "ii", &pid, &priority);
  return sys_setpriority(mrb, PRIO_PROCESS, pid, priority);
}

static mrb_value mrb_getpriority_process_group(mrb_state *mrb, mrb_value self){
  mrb_int pgid;
  mrb_get_args(mrb, "i", &pgid);
  return sys_getpriority(mrb, PRIO_PGRP, pgid);
}

static mrb_value mrb_setpriority_process_group(mrb_state *mrb, mrb_value self){
  mrb_int pgid;
  mrb_int priority;
  mrb_get_args(mrb, "ii", &pgid, &priority);
  return sys_setpriority(mrb, PRIO_PGRP, pgid, priority);
}

static mrb_value mrb_getpriority_user(mrb_state *mrb, mrb_value self){
  mrb_int uid;
  mrb_get_args(mrb, "i", &uid);
  return sys_getpriority(mrb, PRIO_USER, uid);
}

static mrb_value mrb_setpriority_user(mrb_state *mrb, mrb_value self){
  mrb_int uid;
  mrb_int priority;
  mrb_get_args(mrb, "ii", &uid, &priority);
  return sys_setpriority(mrb, PRIO_USER, uid, priority);
}

void mrb_mruby_renice_gem_init(mrb_state *mrb)
{
  struct RClass *renice;
  struct RClass *renice_process;
  struct RClass *renice_process_group;
  struct RClass *renice_user;

  renice               = mrb_define_class(mrb, "Renice", mrb->object_class);
  renice_process       = mrb_define_class_under(mrb, renice, "Process",      mrb->object_class);
  renice_process_group = mrb_define_class_under(mrb, renice, "ProcessGroup", mrb->object_class);
  renice_user          = mrb_define_class_under(mrb, renice, "User",         mrb->object_class);

  // Renice::Process
  mrb_define_class_method(mrb, renice_process, "get", mrb_getpriority_process, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, renice_process, "set", mrb_setpriority_process, MRB_ARGS_REQ(2));
  // Renice::ProcessGroup
  mrb_define_class_method(mrb, renice_process_group, "get", mrb_getpriority_process_group, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, renice_process_group, "set", mrb_setpriority_process_group, MRB_ARGS_REQ(2));
  // Renice::User
  mrb_define_class_method(mrb, renice_user, "get", mrb_getpriority_user, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, renice_user, "set", mrb_setpriority_user, MRB_ARGS_REQ(2));
  DONE;
}

void mrb_mruby_renice_gem_final(mrb_state *mrb)
{
}
