class Tree:
    def __init__(self,v=0):
        self.value = v
        self.children = []
        self.sum = 0

    def display(self):
        result = []
        result.append(self.value)
        self.display_add(result, self.children)
        print(result)

    def display_add(self,result,children):
        if children:
            for i in children:
                result.append([])
                result = result[-1]
                result.append(i.value)
                self.display_add(result, i.children)

    def total(self):
        self.sum += self.value
        self.total_add(self.children)
        print(self.sum)

    def total_add(self,children):
        if children:
            for i in children:
                self.sum += i.value
                self.total_add(i.children)

if __name__ == '__main__':
    tree = Tree(3)
    tree.children.append(Tree(1))
    tree.children.append(Tree(2))
    tree.children[1].children.append(Tree(4))
    tree.display()
    tree.total()

    tree1 = Tree()
    tree1.display()