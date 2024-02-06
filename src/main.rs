use std::{
    fs,
    path::{Path, PathBuf},
};

fn recurse(path: impl AsRef<Path>) -> std::io::Result<Vec<PathBuf>> {
    let mut buf = vec![];
    let entries = fs::read_dir(path)?;

    for entry in entries {
        let entry = entry?;
        let meta = entry.metadata()?;

        if meta.is_dir() {
            let mut subdir = recurse(entry.path())?;
            buf.append(&mut subdir);
        }

        if meta.is_file() {
            buf.push(entry.path());
        }
    }

    Ok(buf)
}
fn main() {
    let files = recurse("../linux").unwrap();
    for file in files {
        let content: Vec<u8> = fs::read(&file).unwrap();
        let uwufied: Vec<u8> = content
            .into_iter()
            .map(|c: u8| match c {
                114 => 119,
                108 => 119,
                82 => 87,
                76 => 87,
                _ => c,
            })
            .collect();

        fs::write(file, uwufied).unwrap();
    }
}
