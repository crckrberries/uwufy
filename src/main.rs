use std::{
    fs,
    path::{Path, PathBuf},
};

fn recurse(path: impl AsRef<Path>) -> Vec<PathBuf> {
    let mut buf = vec![];
    let entries = fs::read_dir(path).unwrap();

    for entry in entries {
        let entry = entry.unwrap();
        let meta = entry.metadata().unwrap();

        if meta.is_dir() {
            let mut subdir = recurse(entry.path());
            buf.append(&mut subdir);
        }

        if meta.is_file() {
            buf.push(entry.path());
        }
    }

    return buf;
}
fn main() {
    let files = recurse("../linux"); // replace with teh path of the file
    for file in files {
        let content: Vec<u8> = fs::read(&file).unwrap();
        let uwufied: Vec<u8> = content
            .into_iter()
            .map(|c: u8| match c {
                114 => 119, // r -> w
                108 => 119, // l -> w
                82 => 87,   // R -> W
                76 => 87,   // L -> W
                _ => c,     // none of those
            })
            .collect();

        fs::write(file, uwufied).unwrap();
    }
}
