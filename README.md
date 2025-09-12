# Commands for Arduino Sketch

| Command | Example | Effect | Notes |
|---------|---------|--------|-------|
| Manual speeds | X400 Y-200 Z100 | Moves motors at specified speeds. Negative = reverse direction. | Speeds update immediately. |
| STOP | STOP | Stops all motors immediately. | Last speeds are remembered for START. |
| START | START | Resumes motors at last remembered speeds. | Works after STOP or RUN. |
| RUN | RUN | Runs the preset speeds (presetX/Y/Z). | Updates last speeds so START resumes them. |
| SET | SET X600 Y100 Z-50 | Updates the preset speeds. | Motors do not change immediately; next RUN uses new values. |
| Partial SET | SET Y250 | Updates only the specified axis preset. | Other axes remain unchanged. |

**Serial Monitor reminders:**
- Baud rate: 115200
- Line ending: Newline
