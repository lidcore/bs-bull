let q = Queue.init("shitballs", "redis://127.0.0.1:6379");

Queue.on(q, `Completed((. _, res) => Js.log(res)));
Queue.on(q, `Drained(() => Js.log("drained")));
Queue.on(q, `Error(err => Js.log(err)));
Queue.on(q, `Paused(() => Js.log("paused")));
Queue.on(q, `Progress((. _, progress) => Js.log(progress)));

Queue.process(
  q,
  ~concurrency=5,
  ~processor="/me/projects/bs-bull/lib/js/examples/exploder.bs.js",
  (),
);

Queue.add(q, {"helloFrom": "earth"});
Queue.add(q, {"helloFrom": "earth"});
