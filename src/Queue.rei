type t;
type job;
type result;

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

let init: (string, string) => t;
let add: (t, Js.t('a)) => unit;
let on: (t, events) => unit;
let process: (t, ~concurrency: int=?, ~processor: string, unit) => unit;
let progress: (job, int) => unit;
