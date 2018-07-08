let dirname: option(string) = [%bs.node __dirname];

let q = Queue.init("exploder", "redis://127.0.0.1:6379");

Queue.on(q, `Completed((. _, res) => Js.log(res)));
Queue.on(q, `Drained(() => Js.log("drained")));
Queue.on(q, `Error(err => Js.log(err)));
Queue.on(q, `Paused(() => Js.log("paused")));
Queue.on(q, `Progress((. _, progress) => Js.log(progress)));

let worker = {j|$(dirname)/exploder.bs.js|j};

Queue.process(q, ~concurrency=5, ~processor=worker, ());

Queue.add(q, {"tick": "tock"});
Queue.add(q, {"tick": "tock"});
Queue.add(q, {"tick": "tock"});
Queue.add(q, {"tick": "tock"});
Queue.add(q, {"tick": "tock"});
