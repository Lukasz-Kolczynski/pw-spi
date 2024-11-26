class Slab:
        def _init_(self, object_size, objs_per_slab = 10): 
                self.slab = []
                self.object_size = object_size
                self.objs_per_slab = objs_per_slab

        def _internal_alloc(self):
                slab = {
                        "memory" : bytearray(self.object_size * self.objs_per_slab),
                        "available": enumerate(self.objs_per_slab) # [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
                }
                self.slab.append(slab)

        def alloc(self):
                for slab in self.slabs:
                        if slab["available"]: 
                                print("ch mp")# if len(slab["available"]) != 0
                
        def free(self):
                pass

struct_size = 200 # bytes
allocator = Slab()
print("duar")