# zmk-config

ZMK firmware configurations for 4 Corne keyboards, sharing one keymap.

## Keyboards

| Branch | BT Name | PCB | Shield | Display | LEDs |
|--------|---------|-----|--------|---------|------|
| `keyboard/corne-snow` | CorneSnow | Low profile metal white (scout armory) | `corne` | OLED | No |
| `keyboard/darkkorn` | DarkKorn | Low profile metal black (scout armory, Typeractive) | `corne` + nice_view_adapter | nice!view | No |
| `keyboard/corne42` | Corne42 | MX 3D printed Chieftain42 | `splitkb_aurora_corne` | nice!view (boge wire, default pin) | No |
| `keyboard/rainbowcorne` | RainbowCorne | MX 3D printed Chieftain42 | `splitkb_aurora_corne` | nice!view (boge wire, CS=P1.01) | RGB (27/half) |

## Branch structure

```
main                    ← shared keymap (config/keymap.h) + helpers
  ├── keyboard/corne-snow
  ├── keyboard/darkkorn
  ├── keyboard/corne42
  └── keyboard/rainbowcorne
```

Each keyboard branch contains only its `build.yaml`, `config/*.conf`, and a
thin `config/*.keymap` wrapper that `#include`s the shared `keymap.h`.

RGB bindings in the ADJUST layer are compiled in/out automatically via
`#ifdef CONFIG_ZMK_RGB_UNDERGLOW` — only RainbowCorne enables this.

## Updating the keymap

Edit `config/keymap.h` on `main`, then rebase all keyboard branches:

```bash
git checkout main
# ... edit config/keymap.h ...
git commit -m "keymap: describe your change"

# Rebase all keyboards (one-liner):
for branch in keyboard/corne-snow keyboard/darkkorn keyboard/corne42 keyboard/rainbowcorne; do
  git checkout $branch && git rebase main
done

# Push all branches to trigger GitHub Actions builds:
git push --all
```

If a rebase has no conflicts (it shouldn't, since keyboard branches only touch
their own conf/build files), it completes automatically. Push each branch to
trigger the GitHub Actions firmware build for that keyboard.

## Per-keyboard files

### keyboard/corne-snow
- `build.yaml` — `corne_left` / `corne_right` (no nice!view)
- `config/corne.conf` — OLED with widgets, no RGB
- `config/corne.keymap` — `#include "keymap.h"`

### keyboard/darkkorn
- `build.yaml` — `corne_left nice_view_adapter nice_view` / right
- `config/corne.conf` — nice!view, no RGB
- `config/corne.keymap` — `#include "keymap.h"`

### keyboard/corne42
- `build.yaml` — `splitkb_aurora_corne_left nice_view_adapter nice_view` / right
- `config/splitkb_aurora_corne.conf` — nice!view, no RGB
- `config/splitkb_aurora_corne.keymap` — `#include "keymap.h"`

### keyboard/rainbowcorne
- `build.yaml` — `splitkb_aurora_corne_left nice_view_adapter nice_view` / right
- `config/splitkb_aurora_corne.conf` — nice!view, RGB enabled
- `config/splitkb_aurora_corne.keymap` — leds.dtsi + CS pin override + `#include "keymap.h"`
- `config/leds.dtsi` — LED chain length (27 per half)

## Firmwares

The `firmwares/` directory is gitignored on all branches. Use it freely to
store downloaded firmware files for any keyboard — it persists across branch
switches.
