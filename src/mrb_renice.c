/*
** mrb_renice.c - Renice class
**
** Copyright (c) takumakume 2017
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_renice.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_renice_data;

static const struct mrb_data_type mrb_renice_data_type = {
  "mrb_renice_data", mrb_free,
};

static mrb_value mrb_renice_init(mrb_state *mrb, mrb_value self)
{
  mrb_renice_data *data;
  char *str;
  int len;

  data = (mrb_renice_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_renice_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_renice_data *)mrb_malloc(mrb, sizeof(mrb_renice_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_renice_hello(mrb_state *mrb, mrb_value self)
{
  mrb_renice_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_renice_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_renice_gem_init(mrb_state *mrb)
{
  struct RClass *renice;
  renice = mrb_define_class(mrb, "Renice", mrb->object_class);
  mrb_define_method(mrb, renice, "initialize", mrb_renice_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, renice, "hello", mrb_renice_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, renice, "hi", mrb_renice_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_renice_gem_final(mrb_state *mrb)
{
}

