type t;
type job;
type result;

[@bs.deriving abstract]
type rateLimiter = {
  [@bs.optional]
  max: int,
  [@bs.optional]
  duration: int,
};

[@bs.deriving abstract]
type redisOptions = {
  [@bs.optional]
  port: int,
  [@bs.optional]
  host: string,
  [@bs.optional]
  db: int,
  [@bs.optional]
  password: string,
};

[@bs.deriving abstract]
type advancedOptions = {
  [@bs.optional]
  lockDuration: int,
};

[@bs.send] external progress : (job, int) => unit = "";

[@bs.module] [@bs.new] external init : (string, string) => t = "bull";

[@bs.send] external add : (t, Js.t('a)) => unit = "";

[@bs.send] external process : (t, int, string) => unit = "";

let process = (q, ~concurrency=1, ~processor, ()) =>
  process(q, concurrency, processor);

type events = [
  | `Active((. job, Js.Promise.t(job)) => unit)
  | `Cleaned((. array(job), string) => unit)
  | `Completed((. job, result) => unit)
  | `Drained(unit => unit)
  | `Error(Js.Exn.t => unit)
  | `Failed((. job, Js.Exn.t) => unit)
  | `Paused(unit => unit)
  | `Progress((. job, int) => unit)
  | `Resumed(job => unit)
  | `Stalled(job => unit)
];

[@bs.send] external on : (t, string, 'a) => unit = "";

let on = q =>
  fun
  | `Active(fn) => on(q, "active", fn)
  | `Cleaned(fn) => on(q, "cleaned", fn)
  | `Completed(fn) => on(q, "completed", fn)
  | `Drained(fn) => on(q, "drained", fn)
  | `Error(fn) => on(q, "error", fn)
  | `Failed(fn) => on(q, "failed", fn)
  | `Paused(fn) => on(q, "paused", fn)
  | `Progress(fn) => on(q, "progress", fn)
  | `Resumed(fn) => on(q, "resumed", fn)
  | `Stalled(fn) => on(q, "stalled", fn);
