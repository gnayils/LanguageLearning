import Cocoa

struct Item {
    
    var id: Int
    
    init(id: Int = -1) {
        self.id = id;
    }
}

class ItemContainer {
    
    var items = [Item]()
    let capacity = 10
    let condition = NSCondition()
    
    
    func put(_ item: inout Item) {
        condition.lock(); defer { condition.unlock() }
        while items.count == capacity {
            print("[PUTTER] item container was full, take a rest...")
            condition.wait()
            print("[PUTTER] wake up")
        }
        if items.count < 10 {
            item.id = items.count
            items.append(item)
            print("put item \(item.id)");
            condition.signal()
        }
    }
    
    func get() -> Item? {
        condition.lock(); defer { condition.unlock() }
        while items.count == 0 {
            print("[GETTER] item container was empty, take a rest...")
            condition.wait()
            print("[GETTER] wake up...")
        }
        if items.count > 0 {
            let item =  items.popLast()
            print("get item \(item?.id)")
            condition.signal()
            return item
        }
        return nil
    }
}

class Worker {
    
    var isWorking = false
    var thread: Thread?
    
    init() {
        self.thread = Thread(target: self, selector:#selector(work), object: nil)
    }
    
    @objc final func work() {
        while isWorking {
            doingWork()
            takeRest()
        }
    }
    
    func doingWork() {
        print("doing work")
    }
    
    final func startWork() {
        isWorking = true
        thread?.start()
    }
    
    final func stopWork() {
        isWorking = false
    }
    
    func takeRest() {
        usleep(arc4random_uniform(500000))
    }
    
}

class Producer : Worker {
    
    let container: ItemContainer
    
    init(_ container: ItemContainer) {
        self.container = container
        super.init()
    }
    
    override func doingWork() {
        var item = Item()
        container.put(&item)
    }
}

class Consumer : Worker {
    
    let container: ItemContainer
    
    init(_ container: ItemContainer) {
        self.container = container
        super.init()
    }
    
    override func doingWork() {
        container.get()
    }
}

let container = ItemContainer()

let producer = Producer(container)
producer.startWork()

let consumer = Consumer(container)
consumer.startWork()

sleep(60)

producer.stopWork()
consumer.stopWork()
