use std::alloc::{Allocator, AllocError, Global, Layout, System};
use std::default::default;
use std::fs::{File, OpenOptions};
use std::io::{Read, Seek, SeekFrom, Write};
use std::ptr::{NonNull, null_mut};
use std::time::Instant;
use bumpalo::Bump;

use crate::doublets::{ILinksExtensions, ILinks, Link};
use crate::doublets::data::IGenericLinks;
use crate::doublets::decorators::NonNullDeletionResolver;
use crate::doublets::mem::united::Links;
use crate::mem::{AllocMem, FileMappedMem, HeapMem, Mem, ResizeableBase, ResizeableMem};
use crate::test_extensions::ILinksTestExtensions;
use crate::tests::make_links;
use crate::tests::make_mem;

#[test]
fn random_creations_and_deletions() {
    std::fs::remove_file("db.links");

    let mem = make_mem();
    let mut links = make_links(mem);
    let mut links = links.decorators_kit();

    let instant = Instant::now();
    links.test_random_creations_and_deletions(1000);

    println!("{:?}", instant.elapsed());
}

#[test]
fn mapping() {
    std::fs::remove_file("map.txt").unwrap();
    let mut mem = FileMappedMem::new("map.txt").unwrap();

    mem.reserve_mem(13370).unwrap();
    mem.reserve_mem(2280).unwrap();

    let mut file = std::fs::File::open("map.txt").unwrap();
    assert_eq!(13370, file.metadata().unwrap().len() as usize);
}

#[test]
fn billion_points_file_mapped() {
    std::fs::remove_file("db.txt");

    let mem = FileMappedMem::new("db.txt").unwrap();
    let mut links = Links::<usize, _>::new(mem);

    let instant = Instant::now();

    for _ in 0..10_000_000 {
        links.create_point();
    }

    println!("{:?}", instant.elapsed());
}

#[test]
fn billion_points_heap_mem() {
    let mem = HeapMem::new();
    let mut links = Links::<usize, _>::new(mem);

    let instant = Instant::now();

    for _ in 0..10_000_000 {
        links.create_point();
    }

    println!("{:?}", instant.elapsed());
}

#[test]
fn billion_points_bump_alloc() {
    let bump = Bump::new();
    let mem = AllocMem::new(&bump);
    let mut links = Links::<usize, _>::new(mem);

    let instant = Instant::now();

    for _ in 0..10_000_000 {
        links.create_point();
    }

    println!("{:?}", instant.elapsed());
}

#[test]
fn many_points_and_searches() {
    let bump = Bump::new();
    let mem = AllocMem::new(System);
    let mut links = Links::<usize, _>::new(mem);

    let instant = Instant::now();
    for _ in 0..1_000_000 {
        links.create_point();
    }
    println!("{:?}", instant.elapsed());

    let instant = Instant::now();
    for i in 1..=1_000_000 {
        // links.search_or(i, i, 0);
        links.get_link(i);
    }
    println!("{:?}", instant.elapsed());
}


#[test]
fn billion_points_file_mapped_splited() {
    std::fs::remove_file("db.txt");

    let mem = FileMappedMem::new("db.txt").unwrap();
    let mut links = Links::<usize, _>::new(mem);

    let instant = Instant::now();

    for _ in 0..10_000_000 {
        links.create_point();
    }

    println!("{:?}", instant.elapsed());
}

#[test]
fn billion_points_heap_mem_splited() {
    let mem = HeapMem::new();
    let mut links = Links::<usize, _>::new(mem);

    let instant = Instant::now();

    for _ in 0..10_000_000 {
        links.create_point();
    }

    println!("{:?}", instant.elapsed());
}

#[test]
fn billion_points_bump_alloc_splited() {
    let bump = Bump::new();
    let mem = AllocMem::new(&bump);
    let mut links = Links::<usize, _>::new(mem);

    let instant = Instant::now();

    for _ in 0..10_000_000 {
        links.create_point();
    }

    println!("{:?}", instant.elapsed());
}

#[test]
fn many_points_and_searches_splited() {
    let bump = Bump::new();
    let mem = AllocMem::new(System);
    let mut links = Links::<usize, _>::new(mem);

    let instant = Instant::now();
    for _ in 0..1_000_000 {
        links.create_point();
    }
    println!("{:?}", instant.elapsed());

    let instant = Instant::now();
    for i in 1..=1_000_000 {
        // links.search_or(i, i, 0);
        links.get_link(i);
    }
    println!("{:?}", instant.elapsed());
}
