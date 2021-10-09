use crate::doublets::mem::united::generic::UpdatePointers;
use crate::num::LinkType;

pub trait ILinksTreeMethods<T: LinkType>: UpdatePointers {
    fn count_usages(&self, root: T) -> T;

    fn search(&self, source: T, target: T) -> T;

    fn each_usages<H: FnMut(&[T]) -> T>(&self, root: T, handler: H) -> T;

    fn detach(&mut self, root: &mut T, index: T);

    fn attach(&mut self, root: &mut T, index: T);
}
